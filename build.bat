@echo off
rem Requires a python 3.6 or higher install to be available in your PATH
python %~dp0\tools\build.py --build_dir %~dp0\build %*