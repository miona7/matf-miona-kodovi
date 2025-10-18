import json

with open("tacke.json", "r") as f:
    tacke = json.load(f)

print(tacke)

print(sorted(tacke, key = lambda t: t["koordinate"][0]**2 + t["koordinate"][1]**2))