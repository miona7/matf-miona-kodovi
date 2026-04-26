-- Record Syntax
-- "konstruktor" sa funkcijama selektorima - "getterima"
data Pet = MkPet { regId :: Int
                 , name :: String
                 , age :: Int
                 , height :: Float
                 , weight :: Float
                 } deriving Show

-- poziciono instanciranje podataka -> moramo redom da navedemo sva polja u konstruktoru TACNIM redosledom
yourPet = MkPet 1 "Lesi" 5 10.5 15.3

-- imenovano -> eksplicitno navodimo polja koja inicijalizujemo, redosled nije bitan
myPet = MkPet { regId = 2, name = "Rex", age = 8, height = 23.4, weight = 33.2 }

-- Record Update
-- ako zelimo da napravimo kopiju postojeceg objekta sa izmenjenim podatkom
myPetYounger = myPet { age = 5 }