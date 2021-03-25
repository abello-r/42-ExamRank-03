rm -rf .mn_test/_gen* .mn_test/_our_.mn_test* .mn_test/_.mn_test* .mn_test/output .mn_test/coutput .mn_test/example_*

cp mini_paint.c .mn_test/mini_paint.c
cd .mn_test
bash test_mini.sh
cd ..