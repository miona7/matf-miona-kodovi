NAPOMENA: Ne dirati tests.cpp i .lines fajlove (mada ih smete kopirati
    u drugi direktorijum ako vam odgovara), oni služe da proverite da
    li ste ispunili zadatak! Testovi se pokreću tako sto pokrenete
    program bez argumenata komandne linije. Ako ste popravili sve
    dobićete adekvatnu poruku kao izlaz. Na dnu se nalazi zadatak.

Tekst: Jedan način predstavljanja pravih linija u rasterskom prostoru
    je rasterizacija. Ideja je da se linija određena početnom i krajnjom 
    tačkom, iako je neprekidna, što vernije predstavi na monitoru koji
    je matrica piksela.

    Tim neiskusnih C++ programera je odlučilo da napravi program koji
    iscrtava linije na matricu bitova.

Proces:
    - Svakoj liniji je pridružen neoznačen broj tako da se linija sa većim
        brojem uvek crta preko linije sa manjim
    - Koraci iscrtavanja jedne linije:
        1. Odredi se rastojanje tačaka po x osi i po y osi (delta x i delta y).
        2. Veća od dve delte nam predstavlja koliko koraka moramo da napravimo
            tako da je u svakom koraku jedna od koordinata uvek celobrojna.
        3. Za svaki korak se odredi koliko trenutni x i y treba da se pomere
            (koliki je inkrement), pretpostavka je da će jedan od inkrementa biti 1
            a drugi će biti neka vrednost u pokretnom zarezu.
        4. Bira se piksel koji je bliži pravoj u odnocu na necelobrojni inkrement
            i popunjava se brojem ukoliko se u polju ne nalazi neki veći.

Zadatak:
    - Inicijalizovati git repozitorijum u folderu "lines".
    - Napraviti build sistem (make/qmake/CMake). Program mora da se
        kompilira sa "-g" flagom. Rezultujući program mora da se zove
        "lines". Napravite novu granu pod nazivom "build", na nju
        smeštajte sve commitove vezane za build sistem. Kada ga 
        završite uradite merge sa glavnom granom.
    - Popraviti sve bagove u programu. Svaka ispravka treba da bude
        jedan commit na glavnoj grani. Commit treba da sadrži SAMO 
        relevantnu izmenu u kodu i ništa više. U commit poruci ukratko 
        opisati ispravku.
    - Pitanje: Da li način testiranja moze da se unapredi?
      Odgovor: ...
