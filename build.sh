DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

#requires python3.6 or higher
python3 $DIR/tools/build.py --build_dir $DIR/build "$@"