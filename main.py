import os
import subprocess

log_ext = '.log'
input_file = 'posDon.txt'

for filename in os.listdir(os.getcwd()):
    f_name, f_ext = os.path.splitext(filename)
    if f_ext == '.txt':
        result_file = f_name+log_ext
        proc = subprocess.Popen(["./xpos_weight_mat", input_file, filename, result_file])
        proc.wait(1000)
    else:
        print('{}'.format(filename))
