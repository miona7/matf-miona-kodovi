select d.IME, d.PREZIME
from DA.DOSIJE d
where exists(
    select *
    from DA.ISPIT i
    where i.INDEKS = d.INDEKS and i.STATUS = 'o' and i.OCENA = 9
);

select d.IME, d.PREZIME
from DA.DOSIJE d
where d.INDEKS in (
    select i.INDEKS
    from DA.ISPIT i
    where i.STATUS = 'o' and i.OCENA = 9
)