import argparse
from os import getcwd
from random import randrange


parser = argparse.ArgumentParser(prog="SudokuGen", description="Generates random nxn sudoku solutions.")
parser.add_argument("-n")
parser.add_argument("-t", "--threads")
parser.add_argument("-f", "--file")

args = parser.parse_args()
n = int(args.n)
threads = int(args.threads)
filename = args.file

nums = []
row = []

for ix in range(n * n + 1):
    if ix and not ix % n:
        nums.append(row)
        row = []
    row.append(str(randrange(1, n + 1)))

nums = [" ".join(row) for row in nums]

with open(fr"{getcwd()}\{filename}", "w") as fp:
    fp.write(f"{threads} {n}\n")
    fp.write("\n".join(nums))
