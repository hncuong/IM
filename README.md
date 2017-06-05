# IM
Code for Influence Maximization Problem

## CELF(Lakshmanan):
To compile the software, run
$ make 

To run the software, use
$ ./InfluenceModels -c <config-file.txt>

In the config file, one can specify various parameters like input file for friendship graph, propagation model etc. 
These options can also be specified on the command line. 
If a parameter is present in both command line and config file, the command line has the preference. 


## IMRank(Wei Chen): 
This folder contains implementation of different algorithms;
s="-imrank" may refer to IMRank;
### input: text file
n, m 
u, v
### Timing
use clock()

## IRIE(Wei Chen): seem like IMRank
README.docx : This folder contains implementation of different algorithms; 
main.cpp can execute many algorithms.
s = "-irie" may refer to IRIE;
### input: text file
n m
u v w1 w2
### Timing 
use QueryPerformanceCounter()

## PMC: 
### input: tsv file
u v w
### Timing: 
use high_resolution_clock() too 



## SIMPath(Lakshmanan):
To compile under Linux, simply type
$ make
To run the executable, just type
$ ./InfluenceModels -c <config-file.txt> […]
([…] means other options can be used.)


## Static:
