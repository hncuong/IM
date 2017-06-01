#bash/bin

echo -n "All influence file will be deleted, sure? [Y/N] "
read tep

if [ $tep != "Y" ] && [ $tep != "y" ]
then 
  exit 1
fi


folder=figure13

MODE_SET=("IC WC")
#MODE_SET=("IC WC LT")
for mode in $MODE_SET
do
  #rm $folder/$1\_$mode\_time*
  #rm $folder/$1\_$mode\_influence*

    for k in 200 150 100 50 1 
        #for k in 100 125 150 175 200
      do
        for round in 10 25 50 75 100 125 150 175 200 250 300   
            do
             
            rm time_tep
            rm spread_tep

            for ((i=1;i<=20;i++))
            do 
                if [ $mode == "IC" ]
                then 
                    ../pmc $1/graph_IC.txt $k $round > result 
                fi

                if [ $mode == "WC" ]
                then                
                    ../pmc $1/graph_WC.txt $k $round > result
                fi
                awk '/Time/ {print $2}' result >> time_tep
                awk -F "=" '/Seed/ {print $2}' result > seedset
                ./MC --count 10000 --dataset $1/ --model $mode --seed seedset > ttep
                awk '/influence/ {print $2}' ttep >> spread_tep
            done
           
            ./st time_tep > tep_time
            sed -i -e '1d' tep_time

            ./st spread_tep > tep_spread
            sed -i -e '1d' tep_spread
            
            awk '{print $5}' tep_time >> $folder/$1\_$mode\_time\_$k            
            
            awk '{print $5}' tep_spread >>$folder/$1\_$mode\_influence\_$k
        done
    done
done  
