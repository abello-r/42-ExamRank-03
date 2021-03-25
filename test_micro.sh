rm -rf .mc_test/_gen* .mc_test/_our_.mc_test* .mc_test/_.mc_test* .mc_test/output .mc_test/coutput .mc_test/example_*

cp micro_paint.c .mc_test/micro_paint.c
cd .mc_test
bash test_micro.sh
cd ..