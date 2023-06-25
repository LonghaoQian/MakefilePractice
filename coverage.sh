#!/bin/bash
./run_ut.sh
# generate gcov
coverage_report_dir="coverage_report"
rm -rf $coverage_report_dir
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
lcov -d build_debug/ut/CMakeFiles/ut_test1.dir/ --capture --output-file app.info
echo "lib dir is $SCRIPT_DIR/lib/*"
lcov --extract app.info "$SCRIPT_DIR/lib/*" -o result.info
genhtml -o $coverage_report_dir result.info