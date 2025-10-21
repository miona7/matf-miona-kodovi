create view p as
    select i.INDEKS, d.IME, d.PREZIME, i.DATPOLAGANJA
    from DA.ISPIT i join DA.DOSIJE d on i.INDEKS = d.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    where i.DATPOLAGANJA is not null and not exists(
        select *
        from DA.ISPIT i1
        where i1.INDEKS = i.INDEKS and i1.DATPOLAGANJA is not null and i1.DATPOLAGANJA > i.DATPOLAGANJA
    )
    group by i.INDEKS, d.IME, d.PREZIME, i.DATPOLAGANJA
    having avg(i.OCENA*1.0) >= 8.0;


select *
from p;