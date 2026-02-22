NAPOMENA: Ne dirati tests.cpp i test.txt, oni služe da proverite da
    li ste ispunili zadatak! Testovi se pokreću tako sto pokrenete
    program bez argumenata komandne linije. Ako ste popravili sve
    dobićete adekvatnu poruku kao izlaz. Na dnu se nalazi zadatak.

Tekst: Jedan način klasterovanja tačaka je algoritam k sredina. Poenta
    je da se veliki skup tačaka nekako grupiše u k unapred određenih
    grupa tako da se u istoj grupi nalaze tačke koje su "blizu" jedna
    drugoj.

    Tim neiskusnih C++ programera je odlučilo da napravi program koji
    u skupu imenovanih tačaka nađe najveći klaster i ispiše te tačke.

Proces:
    1. Generiše se k nasumičnih tačaka (u daljem tekstu centroida)
    2. Svaka tačka iz skupa se pridruži centroidu koji joj je najbliži.
        Jedan klaster je skup tačaka pridružen istom centroidu.
    3. Za svaki klaster se odredi novi centroid koji predstavlja tačku
        koja ima najmanju udaljenost od svih tačaka u svom klasteru.
    4. Dokle god se centroidi "pomeraju" ponavljati korake 2 i 3.
