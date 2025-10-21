with barJedanPolozio as (
    select ID, NAZIV
    from DA.PREDMET
    where exists(
        select *
        from DA.ISPIT
        where IDPREDMETA = ID and  STATUS = 'o' and OCENA > 5
    )
)
select i.INDEKS, bjp.ID, bjp.NAZIV, i.POENI
from DA.ISPIT i join barJedanPolozio bjp on i.IDPREDMETA = bjp.ID and i.STATUS = 'o' and i.OCENA > 5
where not exists(
    select *
    from DA.ISPIT i1
    where i1.INDEKS <> i.INDEKS and i1.IDPREDMETA = bjp.ID and i1.POENI > i.POENI
)
order by bjp.NAZIV