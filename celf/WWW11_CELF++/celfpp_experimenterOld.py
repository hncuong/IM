#!/usr/bin/python

import sys
import subprocess
import os
import psutil
import shutil
import pdb

def init_alloc_core():

	global allocated 
	
	total_cores = psutil.cpu_count()
	
	for i in range(total_cores):
	
		allocated[i] = 0

	return

def return_free_core():

	#select the core having minimum utilization

	global allocated
    
	core_usage_list =  psutil.cpu_percent(interval=1, percpu=True)

	core_index = -1

	min_val = 1000

	for i in range(len(core_usage_list)):

		if not allocated[i] and core_usage_list[i]<=min_val and core_usage_list[i]<=min_util:

			min_val = core_usage_list[i]

			core_index = i

	allocated[core_index] = 1

	if core_index>-1:
	
                return core_index
        else:
                print "no free cores"

                sys.exit(0)


def create_config_file(fileno,seed_val):

        curr_dir = os.getcwd()
 
        os.chdir('input')
        
        with open('config'+str(fileno)+'.txt','w') as f:

                f.write('phase : 10'+'\n')

                f.write('propModel : IC'+'\n')

                f.write('probGraphFile : datasets/grqc_ic.inf'+'\n')

                f.write('mcruns : '+str(10000.0/Cores)+'\n')

                f.write('outdir : output'+'\n')

                f.write('budget : '+str(seed_val)+'\n')

                f.write('celfPlus : 1'+'\n')

                f.write('startIt : 2'+'\n')


        os.chdir(curr_dir)

        return


def run_experiment(seed_val):

	init_alloc_core()
	
	process_stat = [None]*Cores
	
	for i in range(Cores):
	
		core_index = return_free_core()
		
		cmd = "taskset -c {0} ".format(core_index)

                create_config_file(i,seed_val)

		new_cmd = "./InfluenceModels -c "+'config'+str(i)+'.txt'+ ' > '+'./output/'+str(seed_val)+'_'+str(core_index)+'.txt'
		
		cmd = cmd + new_cmd

		print cmd
		
		#process_stat[i] = subprocess.Popen(cmd,shell=True)
		
	#exit_code = [p.wait() for p in process_stat]

	#print exit_code	
		
	return
	
	

def run_experiments():

        seeds = [1]
	
	for s in seeds:
	
		run_experiment(s)

	return



	

def main():

	if len(sys.argv)!=2:

		print "usage python experiments.py <#cores>"

		sys.exit(0)

	global min_util,allocated,Cores
	
	allocated = {}
	
	min_util = 10.0

	Cores = int(sys.argv[1])

	if not os.path.exists('input'):

            os.makedirs('input')

        if not os.path.exists('output'):

            os.makedirs('output')

	run_experiments()
	
	return


if __name__=='__main__':
    main()
