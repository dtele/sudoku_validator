import re
import subprocess
from os import chdir, getcwd

from matplotlib import pyplot as plt
from matplotlib import rcParams


path = f"{getcwd()}/"
chdir(path)

rcParams["figure.figsize"] = (10, 7)
rcParams["font.family"] = "Times New Roman"

experiment_one = {"nonthreads": [], "pthread": [], "openmp": []}
for n in range(2, 9):
    subprocess.run(f"py {path}gen.py -n {n ** 2} -t 4 -f sudoku.txt")
    for i in experiment_one.keys():
        raw_output = subprocess.run(path + f"{i}.exe", capture_output=True)
        output = raw_output.stdout.decode().split()
        experiment_one.update({i: experiment_one[i] + [(int(output[2]), int(output[4]), float(output[-2]))]})

experiment_two = {"nonthreads": [], "pthread": [], "openmp": []}
for t in range(2, 32 + 1, 2):
    subprocess.run(f"py {path}gen.py -n 25 -t {t} -f sudoku.txt")
    for i in experiment_two.keys():
        raw_output = subprocess.run(path + f"{i}.exe", capture_output=True)
        output = raw_output.stdout.decode().split()
        experiment_two.update({i: experiment_two[i] + [(int(output[2]), int(output[4]), float(output[-2]))]})

for ix, key in enumerate(experiment_one.keys()):
    plt.plot([i[0] for i in experiment_one[key]], [i[2] for i in experiment_one[key]], label=key,
             color=["#B6465F", "#00B295", "#191516"][ix])

plt.legend()
plt.suptitle("Experiment 1: Varying Size of Sudoku", fontsize=16, y=0.96)
plt.title("k = 4", fontsize=12)
plt.xlabel("Size of Sudoku")
plt.xticks([i ** 2 for i in range(2, 9)])
plt.ylabel("Time Taken (logarithmic)")
plt.yscale("log")
plt.show()

for ix, key in enumerate(experiment_two.keys()):
    plt.plot([i[1] for i in experiment_two[key]], [i[2] for i in experiment_two[key]], label=key,
             color=["#B6465F", "#00B295", "#191516"][ix])

plt.legend()
plt.suptitle("Experiment 2: Varying Number of Threads", fontsize=16, y=0.96)
plt.title("n = 25", fontsize=12)
plt.xlabel("Number of Threads")
plt.xticks(range(2, 32 + 1, 2))
plt.ylabel("Time Taken (logarithmic)")
plt.yscale("log")
plt.show()
