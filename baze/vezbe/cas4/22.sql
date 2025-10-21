select substr(i1.INDEKS, 5) || '/' || substr(i1.INDEKS, 1, 4)
from DA.ISPIT i1
where i1.STATUS = 'o' and i1.OCENA = 10 and not exists(
    select *
    from DA.ISPIT i2
    where i1.INDEKS <> i2.INDEKS and i2.STATUS = 'o' and i2.OCENA = 10 and i1.IDPREDMETA = i2.IDPREDMETA
)