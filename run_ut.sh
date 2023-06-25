

utDir="build_debug/ut/"
gTestFlags="--gtest_repeat=20 --gtest_shuffle"
gTestSeed="--gtest_random_seed=1020"
utResults="ut_results.txt"
utResultsDir="ut/results/"
outputDir="ut/report/"
utDataBinaryDir="ut/data/binary_test"
utDataCsvDir="ut/data/csv_test"
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
# create directory
if [ ! -d $utDataBinaryDir ]; then
    mkdir $utDataBinaryDir
fi
if [ ! -d $utDataCsvDir ]; then
    mkdir $utDataCsvDir
fi
# then run all tests
for testName in $testSet
do
$"$utDir$testName" --gtest_brief=1 $gTestFlags $gTestSeed --gtest_output=xml:$outputDir$testName > $utResultsDir$utResults
done

./ut_scan.sh $utResultsDir$utResults
finalResults=$?
exit $finalResults