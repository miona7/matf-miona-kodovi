class Robot:
    populacija = 0

    def __init__(self, ime):
        self.ime = ime
        Robot.populacija += 1
        print("{} je kreiran!".format(self.ime))

    def __del__(self):
        Robot.populacija -= 1
        print("{} je unisten!".format(self.ime))

    def oglasi_se(self):
        print("{} kaze cao!".format(self.ime))
    
    @classmethod
    def broj_robota(klasa):
        print(klasa.populacija)


if __name__ == '__main__':
    r1 = Robot("miona")
    r2 = Robot("marko")
    r3 = Robot("rajko")

    r1.oglasi_se()
    r2.oglasi_se()
    r3.oglasi_se()

    Robot.broj_robota()

    del r3

    Robot.broj_robota()

