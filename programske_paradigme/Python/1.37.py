import json

with open("datoteka.txt", "r") as f:
    x = json.load(f)
    print(x["ime"])
    print(x["prezime"])
    print(x["godine"])