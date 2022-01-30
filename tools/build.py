import sys
import os
import argparse
import shutil
import subprocess
from util import run, get_logger   # noqa: E402

log = get_logger("build")

class BaseError(Exception):
    """Base class for errors originating from build.py."""
    pass


class BuildError(BaseError):
    """Error from running build steps."""

    def __init__(self, *messages):
        super().__init__("\n".join(messages))


class UsageError(BaseError):
    """Usage related error."""

    def __init__(self, message):
        super().__init__(message)


def _check_python_version():
    # According to the BUILD.md, python 3.5+ is required:
    # Python 2 is definitely not supported and it should be safer to consider
    # it won't run with python 4:
    if sys.version_info[0] != 3:
        raise BuildError(
            "Bad python major version: expecting python 3, found version "
            "'{}'".format(sys.version))
    if sys.version_info[1] < 5:
        raise BuildError(
            "Bad python minor version: expecting python 3.5+, found version "
            "'{}'".format(sys.version))

_check_python_version()

def resolve_executable_path(command_or_path):
    """Returns the absolute path of an executable."""
    executable_path = shutil.which(command_or_path)
    if executable_path is None:
        raise BuildError("Failed to resolve executable path for "
                         "'{}'.".format(command_or_path))
    return os.path.realpath(executable_path)

def is_windows():
    return sys.platform.startswith("win")


def is_macOS():
    return sys.platform.startswith("darwin")


def is_linux():
    return sys.platform.startswith("linux")

def run_subprocess(args, cwd=None, capture_stdout=False, dll_path=None,
                   shell=False, env={}):
    if isinstance(args, str):
        raise ValueError("args should be a sequence of strings, not a string")

    my_env = os.environ.copy()
    if dll_path:
        if is_windows():
            my_env["PATH"] = dll_path + os.pathsep + my_env["PATH"]
        else:
            if "LD_LIBRARY_PATH" in my_env:
                my_env["LD_LIBRARY_PATH"] += os.pathsep + dll_path
            else:
                my_env["LD_LIBRARY_PATH"] = dll_path

    my_env.update(env)

    return run(*args, cwd=cwd, capture_stdout=capture_stdout, shell=shell, env=my_env)


def update_submodules(source_dir):
    run_subprocess(["git", "submodule", "sync", "--recursive"], cwd=source_dir)
    run_subprocess(["git", "submodule", "update", "--init", "--recursive"],
                   cwd=source_dir)

def get_config_build_dir(build_dir, config):
    # build directory per configuration
    return os.path.join(build_dir, config)

def clean_targets(cmake_path, build_dir, configs):
    for config in configs:
        log.info("Cleaning targets for %s configuration", config)
        build_dir2 = get_config_build_dir(build_dir, config)
        cmd_args = [cmake_path,
                    "--build", build_dir2,
                    "--config", config,
                    "--target", "clean"]

        run_subprocess(cmd_args)

def generate_build_tree(cmake_path, source_dir, build_dir, configs, cmake_extra_defines, 
                        args, cmake_extra_args):
    log.info("Generating CMake build tree")
    cmake_dir = source_dir
    cmake_args = [
        cmake_path, cmake_dir,
    ]

    cmake_args += ["-D{}".format(define) for define in cmake_extra_defines]
    cmake_args += cmake_extra_args

    for config in configs:
        config_build_dir = get_config_build_dir(build_dir, config)
        os.makedirs(config_build_dir, exist_ok=True)
        run_subprocess(
            cmake_args + [
                "-DCMAKE_BUILD_TYPE={}".format(config),
            ],
            cwd=config_build_dir
        )


def build_targets(args, cmake_path, build_dir, configs, num_parallel_jobs, target=None):
    for config in configs:
        log.info("Building targets for %s configuration", config)
        build_dir2 = get_config_build_dir(build_dir, config)
        cmd_args = [cmake_path,
                    "--build", build_dir2,
                    "--config", config]
        if target:
            cmd_args.extend(['--target', target])

        build_tool_args = []
        if num_parallel_jobs != 1:
            if is_windows() and args.cmake_generator != 'Ninja':
                build_tool_args += [
                    "/maxcpucount:{}".format(num_parallel_jobs),
                    # if nodeReuse is true, msbuild processes will stay around for a bit after the build completes
                    "/nodeReuse:False",
                ]
            elif (is_macOS() and args.use_xcode):
                # CMake will generate correct build tool args for Xcode
                cmd_args += ["--parallel", str(num_parallel_jobs)]
            else:
                build_tool_args += ["-j{}".format(num_parallel_jobs)]

        if build_tool_args:
            cmd_args += ["--"]
            cmd_args += build_tool_args

        env = {}

        run_subprocess(cmd_args, env=env)

def run_tests(args, source_dir, configs):
    for config in configs:
        if is_windows():
            test_path = os.path.join(source_dir,"bin",config,"leetcodenotes_test.exe")
        else:
            test_path = os.path.join(source_dir,"bin","leetcodenotes_test")
        cmd_args = [test_path,]
        run_subprocess(cmd_args)



def parse_arguments():
    parser = argparse.ArgumentParser(
        description="LeetcodeNotebooks CI build driver.",
        usage="""  # noqa
        Default behavior is --update --build --test for native architecture builds.
        Default behavior is --update --build for cross-compiled builds.

        The Update phase will update git submodules, and run cmake to generate makefiles.
        The Build phase will build all projects.
        The Test phase will run all unit tests, and optionally the ONNX tests.

        Use the individual flags to only run the specified stages.
        """)
    # Main arguments
    parser.add_argument(
        "--build_dir", required=True, help="Path to the build directory.")
    parser.add_argument(
        "--config", nargs="+", default=["Release"],
        choices=["Debug", "Release"],
        help="Configuration(s) to build.")
    parser.add_argument(
        "--update", action='store_true', help="Update makefiles.")
    parser.add_argument("--build", action='store_true', help="Build.")
    parser.add_argument(
        "--clean", action='store_true',
        help="Run 'cmake --build --target clean' for the selected config/s.")
    parser.add_argument(
        "--parallel", nargs='?', const='0', default='1', type=int,
        help="Use parallel build. The optional value specifies the maximum number of parallel jobs. "
             "If the optional value is 0 or unspecified, it is interpreted as the number of CPUs.")
    parser.add_argument("--test", action='store_true', help="Test project")
    
    # Arguments needed by CI
    parser.add_argument(
        "--cmake_path", default="cmake", help="Path to the CMake program.")
    parser.add_argument(
        "--skip_submodule_sync", action='store_true', help="Don't do a "
        "'git submodule update'. Makes the Update phase faster.")
    parser.add_argument(
        "--cmake_generator",
        choices=['Visual Studio 15 2017', 'Visual Studio 16 2019', 'Ninja'],
        default='Visual Studio 16 2019' if is_windows() else None,
        help="Specify the generator that CMake invokes. "
        "This is only supported on Windows")
    
    # Build options
    parser.add_argument(
        "--cmake_extra_defines", nargs="+",
        help="Extra definitions to pass to CMake during build system "
        "generation. These are just CMake -D options without the leading -D.")
    parser.add_argument(
        "--target",
        help="Build a specific target, e.g. winml_dll")
    
    return parser.parse_args()

def main():
    args = parse_arguments()
    cmake_extra_defines = (args.cmake_extra_defines
                           if args.cmake_extra_defines else [])

    configs = set(args.config)

    # setup paths and directories
    cmake_path = resolve_executable_path(args.cmake_path)
    build_dir = args.build_dir
    script_dir = os.path.realpath(os.path.dirname(__file__))
    source_dir = os.path.normpath(os.path.join(script_dir, ".."))

    os.makedirs(build_dir, exist_ok=True)

    log.info("Build started")

    if args.update:
        cmake_extra_args = []
        if not args.skip_submodule_sync:
            update_submodules(source_dir)
        if is_windows():
            cmake_extra_args = [
                '-A', 'x64', '-T', 'host=x64', '-G', args.cmake_generator
            ]

        generate_build_tree(
            cmake_path, source_dir, build_dir, configs, cmake_extra_defines, 
            args, cmake_extra_args)

    if args.clean:
        clean_targets(cmake_path, build_dir, configs)

    if args.build:
        num_parallel_jobs = os.cpu_count() if args.parallel == 0 else args.parallel
        build_targets(args, cmake_path, build_dir, configs, num_parallel_jobs, args.target)
    
    if args.test:
        run_tests(args, source_dir, configs)

if __name__ == '__main__':
    try:
        sys.exit(main())
    except BaseError as e:
        log.error(str(e))
        sys.exit(1)