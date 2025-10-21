select d.IME, d.PREZIME
from DA.DOSIJE d
where d.INDEKS in (
    select INDEKS
    from DA.PRIZNATISPIT
);

select d.IME, d.PREZIME
from DA.DOSIJE d
where exists (
    select *
    from DA.PRIZNATISPIT pi
    where d.INDEKS = pi.INDEKS
);