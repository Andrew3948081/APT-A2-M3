#! /usr/bin/bash


for i in {9..50}
do
    #i=50
    testNum=test$i
    #echo $testNum
    ./ppd stock.dat coins.dat < tests/$testNum.input > tests/$testNum.actual_ppd_out true
    diff  -w tests/$testNum.output tests/$testNum.actual_ppd_out
done

# for i in {0..8}
# do
#     testing=test$i
#     # chmod +x tests/$testing.sh
#     ./tests/$testing.sh
# done
