import os
import sys
import subprocess

model_file = "data/posDon.txt" # file used to generate the position weight matrix model.

path = "data/"
dirs = os.listdir(path)

for i, file_name in enumerate(dirs):
    f_name, f_ext = os.path.splitext(file_name)
    if f_ext == '.txt':
        input_file = "data/" + file_name
        proc = subprocess.Popen(["./xpos_weight_mat", model_file, input_file])
        proc.wait()
    else:
        print('{}'.format(file_name))
