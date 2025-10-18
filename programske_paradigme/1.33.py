with open("datoteka.txt", "r") as f:
    for line in f.readlines():
        for c in line:
            print(c)