
import os
import numpy as np
import glob
import math
import sys


def main():


    if len(sys.argv)<2:

        print "usage python result_aggregator.py <path to directory>"

        sys.exit()


    os.chdir(sys.argv[1])

    mem = []

    spread = []

    tt = []

    if os.path.isfile('results.txt'):

        os.system('rm -f results.txt')

    for file_name in os.listdir(os.getcwd()):

	seeds = str(file_name).split('_')[0]

	with open(file_name) as f:

	  data = f.readlines()

	  lines = []

	  i = 0
		
	  while i<len(data):

	    if data[i].startswith('Picked'):
		

	      lines.append(data[i+1])
		
	    i+=1

	  vals = lines[-1].split(' ')
	
	  mem.append(float(vals[4]))

	  spread.append(float(vals[2]))

	  tt.append(float(vals[5]))


    with open('results.txt','w') as f:

        f.write("#seeds : "+seeds+'\n')

        f.write("Spread : mean = "+str(np.mean(spread))+" std dev = "+str(np.std(spread))+'\n')

        f.write("Memory : mean = "+str(np.mean(mem))+" MB std dev = "+str(np.std(mem))+' MB '+'\n')

        f.write("Total Time : mean = "+str(np.mean(tt))+" min std dev = "+str(np.std(tt))+' min '+'\n')

        

    
    return


if __name__=="__main__":

  main()
