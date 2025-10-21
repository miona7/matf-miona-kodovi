select d1.INDEKS, d2.INDEKS, d1.MESTORODJENJA
from DA.DOSIJE d1 join DA.DOSIJE d2 on d1.MESTORODJENJA = d2.MESTORODJENJA
where d1.MESTORODJENJA like '_____evo' and year(d1.DATUPISA) in (2012, 2015, 2018)
    and year(d2.DATUPISA) in (2012, 2015, 2018) and d1.INDEKS < d2.INDEKS;

with tmp as (
    select INDEKS, MESTORODJENJA
    from DA.DOSIJE
    where year(DATUPISA) in (2012, 2015, 2018) and MESTORODJENJA like '_____evo'
)
select d.INDEKS, t.INDEKS, d.MESTORODJENJA
from DA.DOSIJE d join tmp t on d.MESTORODJENJA = t.MESTORODJENJA and d.INDEKS < t.INDEKS
where year(d.DATUPISA) in (2012, 2015, 2018)