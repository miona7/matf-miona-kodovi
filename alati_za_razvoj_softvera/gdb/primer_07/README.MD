NAPOMENA: Ne dirati tests.cpp i test direktorijum, oni služe da proverite
    da li ste ispunili zadatak! Testovi se pokreću tako sto pokrenete
    program sa putanjom do test direktorijuma kao argument komandne linije.
    Ako ste popravili sve dobićete adekvatnu poruku kao izlaz. Na dnu se 
    nalazi zadatak.

Tekst: Tim neiskusnih C++ programera je odlučilo da napravi program koji
    u tekstualnom fajlu sva pojavljivanja jedne reči zamenjuje drugom.

Proces:
    - Prvi argument je tekst nad kojim se vrše izmene
    - Drugi argument je fajl u kojem je u svakoj liniji opisana naredba
        zamenjivanja teksta.
    - Svaka linija drugog fajla je podeljena karakterom '-' na više
        reči (beline oko karaktera '-' se zanemaruju)
    - Ukoliko u liniji ima više reči, sva pojavljivanja prethodnih se
        zamenjuju poslednjom u nizu.
    - Ukoliko u liniji ima samo jedna reč, ta reč se briše iz teksta

Zadatak:
    - Inicijalizovati git repozitorijum u folderu "text".
    - Popraviti sve bagove u programu. Svaka ispravka treba da bude
        jedan commit. Commit treba da sadrži SAMO relevantnu izmenu u
        kodu i ništa više. U commit poruci u jednoj rečenici opisati
        ispravku.
    - Napraviti build sistem (make/qmake/CMake). Program mora da se
        kompilira sa "-g" flagom. Rezultujući program mora da se zove
        "text". Napraviti granu koja se zove "build", sav kod relevantan
        za build sistem commitovati na toj grani, i na kraju granu "build"
        rebaseovati na glavnu granu.
