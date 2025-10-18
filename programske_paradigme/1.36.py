import json

ime = input("Unesite ime: ")
prezime = input("Unesite prezime: ")
godine = int(input("Unesite godine: "))

junak = {
    "ime" : ime,
    "prezime" : prezime,
    "godine" : godine
}

print(json.dumps(junak))

with open("datoteka.txt", "w") as f:
    json.dump(junak, f)