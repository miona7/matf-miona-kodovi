select INDEKS, IME || ' ' || PREZIME "ime i prezime", replace(MESTORODJENJA, 'Beograd', 'Bg') "mesto rodjenja",
    substr(IME, 1, 1) || substr(PREZIME, 1, 1) inicijali
from DA.DOSIJE