# TO DO: add parse based on python cppcheck --enable=all
# --verbose --xml-version=2 lib --output-file="cppcheck_results.xml"
scan_dir="lib src design_mode_test"
output_file_name="--output-file="cppcheck_results.txt""
warning_flags="--enable=all --verbose"
report_format="|{id}|{severity}|{file}|{line}|{message}"
cppcheck $warning_flags --template=$report_format $scan_dir $output_file_name