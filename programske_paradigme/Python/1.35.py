with open("datoteka.txt", "a+") as f:
    f.write("\nwater\n")
    f.seek(0,0)
    print(f.read())