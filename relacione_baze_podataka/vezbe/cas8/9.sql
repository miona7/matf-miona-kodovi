create function prosek(f_indeks integer)
returns float
return
    select avg(OCENA*1.0)
    from DA.ISPIT
    where INDEKS = f_indeks and STATUS = 'o' and OCENA > 5;

drop function prosek;

select IME, PREZIME, INDEKS, DA.prosek(INDEKS)
from DA.DOSIJE;