select p.NAZIV
from DA.PREDMET p
where not exists(
    select *
    from DA.SKOLSKAGODINA sk
    where not exists(
        select *
        from DA.KURS k
        where k.SKGODINA = sk.SKGODINA and k.IDPREDMETA = p.ID
    )
);

