select d.INDEKS, d.IME, d.PREZIME, uk.SKGODINA, p.NAZIV, p.ESPB
from DA.DOSIJE d join DA.UPISANKURS uk on d.INDEKS = uk.INDEKS
    join DA.PREDMET p on uk.IDPREDMETA = p.ID
where p.ESPB in (5, 10, 12, 25) and p.NAZIV like 'Pr%o%' and uk.SKGODINA between 2016 and 2021