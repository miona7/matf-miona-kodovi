with rokovi_sa_bar_2_polozena as (
    select OZNAKAROKA, SKGODINA, INDEKS
    from DA.ISPIT
    where STATUS = 'o' and OCENA > 5
    group by OZNAKAROKA, SKGODINA, INDEKS
    having count(*) >= 2
)
select count(distinct OZNAKAROKA || SKGODINA)
from rokovi_sa_bar_2_polozena