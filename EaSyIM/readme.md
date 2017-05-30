## Compile
    g++  src/easyim.cpp -Wall -std=c++0x -O3 src/sfmt/SFMT.c  -o easyim
## Execute
    Example:
            ./easyim -dataset nethept/ -l 3 -k 50 -model IC -time 1
    
        Arguments:
            -model:
                the diffusion model uses
                IC or LT or WC
    
            -dataset:
                path to the dataset directory
    
            -l:
                maximum length of simple paths
    
            -k:
                number of selected nodes
                
            -time:
                number of times to run IM
## Dataset Format
    Three files are necessary inside path_to_dataset folder

## Format for attribute
    Location:
        path_to_dataset/attribute.txt
    Format:
        This file should have exactly two lines
        n=number of nodes
        m=number of edges

### Format for IC model
    Location:
        path_to_dataset/graph_ic.inf
    Format:
        Each line has three numbers
        node1 node2 propogation_probability_from_node1_to_node2
    Comments:
        It is always a directed graph
        node number should range in [0 to n-1] (inclusive)

### Format for LT model
    Location:
        path_to_dataset/graph_lt.inf
    Format is same as IC model
                