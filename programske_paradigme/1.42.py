import os

for file in os.listdir(os.curdir):
    if os.path.isfile(os.path.join(os.curdir, file)):
        print(os.path.abspath(os.path.join(os.curdir, file)))