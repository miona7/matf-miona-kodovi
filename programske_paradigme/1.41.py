import os

for (cur_dir, sub_dirs, files) in os.walk(os.pardir):
    print(cur_dir)
    for file in files:
        print(file)
    print()