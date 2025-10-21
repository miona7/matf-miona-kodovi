with br_osmica as (
    select INDEKS, count(*) br_8
    from DA.ISPIT
    where STATUS = 'o' and OCENA = 8
    group by INDEKS
), br_devetki as (
    select INDEKS, count(*) br_9
    from DA.ISPIT
    where STATUS = 'o' and OCENA = 9
    group by INDEKS
)
select distinct d.INDEKS, coalesce((select br_8 from br_osmica where d.INDEKS = br_osmica.INDEKS), 0),
                 coalesce((select br_9 from br_devetki where d.INDEKS = br_devetki.INDEKS), 0)
from DA.DOSIJE d
order by d.INDEKS