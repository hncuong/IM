#!/usr/bin/python

import sys
import subprocess
import os
import psutil
import shutil
import pdb

method_command = {'celf': '','ldag': '','easyim': '', 'imm': '', 'imrank': '', 'irie': '', 
'pmc': '', 'simpath': '', 'static': '', 'tim': '' }

class Arguments(object):
    def __init__(self, method_name, dataset, model, num_seeds, **kwargs):
        self.method_name = method_name
        self.dataset = dataset
        self.model = model
        self.num_seeds = num_seeds
        self.others = {}
        for (arg, val) in kwargs.iteritems():
            self.others[arg] = val

    def generate_im_shell_command():
        
