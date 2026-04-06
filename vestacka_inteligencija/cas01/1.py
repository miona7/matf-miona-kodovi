import sys # omogucava pristup sistemskim parametrima
import os

def saberi(a:int, b:int) -> int:
    return a + b

def cat(args):
    if len(args) != 3:
        print("usage python 1.py cat path")
        sys.exit(1)

    with open(args[2], "r") as f:
        print(f.read())

def cp(args):
    if len(args) != 4:
        print("usage python 1.py cp input output")
        sys.exit(1)

    with open(args[2], "r") as f_input:
        with open(args[3], "w") as f_output:
            f_output.write(f_input.read())

def ls(args):
    if len(args) != 3:
        print("usage python 1.py ls path")
        sys.exit(1)

    for item in os.listdir(args[2]):
        print(item)

commands = {
    "cat" : cat,
    "cp" : cp,
    "ls" : ls
}

try:
    cmd = commands[sys.argv[1]]
    cmd(sys.argv)
except KeyError:
    print("invalid command")
    sys.exit(1)