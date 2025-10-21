select p.NAZIV
from DA.PREDMET p
where exists(
    select *
    from DA.ISPIT i
    where i.IDPREDMETA = p.ID and i.STATUS not in ('p', 'n') and i.INDEKS = 20170022
);

select p.NAZIV
from DA.PREDMET p
where p.ID in (
    select i.IDPREDMETA
    from DA.ISPIT i
    where i.STATUS not in ('p', 'n') and i.INDEKS = 20170022
);

