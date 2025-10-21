with polozilo_vise_od_deset as (
    select i.INDEKS
    from DA.ISPIT i join DA.PREDMET p on i.IDPREDMETA = p.ID and i.STATUS = 'o' and i.OCENA > 5
    group by i.INDEKS
    having sum(p.ESPB) > 10
)
select count(*)
from polozilo_vise_od_deset