

utDir="build/ut/"
gTestFlags="--gtest_repeat=20 --gtest_shuffle"
gTestSeed="--gtest_random_seed=1020"
outputDir="ut/report/"
# init execution list
testSet=()
# define all tests
testSet+="ut_test1"
# clear all old files in the report dir
rm -rf $outputDir*
# then run all tests
for testName in $testSet
do
$"$utDir$testName" $gTestFlags $gTestSeed --gtest_output=xml:$outputDir$testName
done