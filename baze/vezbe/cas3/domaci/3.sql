select *
from DA.DOSIJE d
where not exists(
    select *
    from DA.PREDMET p
    where p.ESPB = 30 and not exists(
        select *
        from DA.ISPIT i
        where i.INDEKS = d.INDEKS and i.IDPREDMETA = p.ID and i.STATUS not in ('p', 'n')
    )
)