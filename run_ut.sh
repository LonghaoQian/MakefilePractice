

utDir="build_debug/ut/"
gTestFlags="--gtest_repeat=20 --gtest_shuffle"
gTestSeed="--gtest_random_seed=1020"
utResults="ut_results.txt"
utResultsDir="ut/results/"
outputDir="ut/report/"
# init execution list
testSet=()
# define all tests
testSet+="ut_test1"
# clear all old files in the report dir
rm -rf $outputDir*
# store the ut result
if [ ! -d $utResultsDir ]; then
    mkdir $utResultsDir
fi
# checkwether ut_result exits
if [ -f $utResultsDir$utResults ]; then
    echo "$utResults exits. removing..."
    rm $utResultsDir$utResults
fi
touch $utResultsDir$utResults
# then run all tests
for testName in $testSet
do
$"$utDir$testName" --gtest_brief=1 $gTestFlags $gTestSeed --gtest_output=xml:$outputDir$testName > $utResultsDir$utResults
done
# generate gcov
coverage_report_dir="coverage_report"
rm -rf $coverage_report_dir
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
lcov -d build_debug/ut/CMakeFiles/ut_test1.dir/ --capture --output-file app.info
echo "lib dir is $SCRIPT_DIR/lib/*"
lcov --extract app.info "$SCRIPT_DIR/lib/*" -o result.info
genhtml -o $coverage_report_dir result.info