select *
from DA.PREDMET p
where not exists(
    select *
    from DA.ISPIT i
    where i.IDPREDMETA = p.ID and i.STATUS not in ('p', 'n') and not exists(
        select *
        from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
        where d.INDEKS = i.INDEKS and d.MESTORODJENJA = 'Berane' and sp.OZNAKA = 'I'
    )
)