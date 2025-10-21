select p.NAZIV
from DA.PREDMET p
where exists(
    select *
    from DA.ISPIT i
    where i.IDPREDMETA = p.ID and i.STATUS = 'o' and i.OCENA > 5 and i.INDEKS = 20170022
)