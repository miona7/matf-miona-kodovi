select d1.IME, d1.PREZIME
from DA.DOSIJE d1
where exists(
    select *
    from DA.DOSIJE d2
    where d1.INDEKS <> d2.INDEKS and d1.MESTORODJENJA = d2.MESTORODJENJA
    and d2.DATUPISA - 1 years = d1.DATUPISA
)