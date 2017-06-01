#!/bin/bash 


rm result time_tep spread_tep

for ((i=1;i<=$2;i++))
do
    ../pmc $1/graph_IC.txt 200 $3 > result

    awk '/Time/ {print $2}' result >> time_tep
    awk -F "=" '/Seed/ {print $2}' result > seedset
    ./MC --count 10000 --dataset $1/ --model IC --seed seedset > ttep
    awk '/influence/ {print $2}' ttep >> spread_tep
done
./st time_tep
./st spread_tep
