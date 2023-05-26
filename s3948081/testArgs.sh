#! /usr/bin/bash

./ppd > peter/test0.actual_ppd_output
./ppd 1 1 < tests/test1.input > peter/test1.actual_ppd_output
./ppd "test dats"/stocktest2.dat coins.dat > peter/test2.actual_ppd_output
./ppd "test dats"/stocktest3-1.dat coins.dat > peter/test3-1.actual_ppd_output
./ppd "test dats"/stocktest3-2.dat coins.dat > peter/test3-2.actual_ppd_output
./ppd "test dats"/stocktest3-3.dat coins.dat > peter/test3-3.actual_ppd_output
./ppd "test dats"/stocktest4-1.dat coins.dat > peter/test4-1.actual_ppd_output
./ppd "test dats"/stocktest4-2.dat coins.dat > peter/test4-2.actual_ppd_output
./ppd "test dats"/stocktest4-3.dat coins.dat > peter/test4-3.actual_ppd_output
./ppd "test dats"/stocktest4-4.dat coins.dat > peter/test4-4.actual_ppd_output
./ppd "test dats"/stocktest4-5.dat coins.dat > peter/test4-5.actual_ppd_output
./ppd "test dats"/stocktest5-1.dat coins.dat > peter/test5-1.actual_ppd_output
./ppd "test dats"/stocktest5-2.dat coins.dat > peter/test5-2.actual_ppd_output
./ppd "test dats"/stocktest5-3.dat coins.dat > peter/test5-3.actual_ppd_output
./ppd stock.dat "test dats"/cointest6.dat > peter/test6.actual_ppd_output
./ppd stock.dat "test dats"/cointest7-1.dat > peter/test7-1.actual_ppd_output
./ppd stock.dat "test dats"/cointest7-2.dat > peter/test7-2.actual_ppd_output
./ppd stock.dat "test dats"/cointest7-3.dat > peter/test7-3.actual_ppd_output
./ppd stock.dat "test dats"/cointest8-1.dat > peter/test8-1.actual_ppd_output
./ppd stock.dat "test dats"/cointest8-2.dat > peter/test8-2.actual_ppd_output
./ppd stock.dat "test dats"/cointest8-3.dat > peter/test8-3.actual_ppd_output
./ppd stock.dat "test dats"/cointest8-4.dat > peter/test8-4.actual_ppd_output