try:
    with open("datoteka.txt", "r") as f:
        for line in f:
            print(line)
except IOError as e:
    print(e)