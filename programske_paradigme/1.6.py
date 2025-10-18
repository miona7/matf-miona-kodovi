def radni_dan(dan):
    if dan % 7 == 6 or dan % 7 == 0:
        return False
    else:
        return True
    
for i in range(10):
    dan = int(input("Unesite dan: "))
    if radni_dan(dan):
        print("Dan {0:d} je radan".format(dan))
    else:
        print("Dan {0:d} je neradan".format(dan))