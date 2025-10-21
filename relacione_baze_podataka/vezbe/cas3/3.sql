select distinct i.INDEKS
from DA.ISPIT i
where i.STATUS = 'o' and i.OCENA > 5 and i.IDPREDMETA not in (
    select i2.IDPREDMETA
    from DA.ISPIT i2
    where i2.INDEKS = 20170022 and i2.STATUS = 'o' and i2.OCENA > 5
)