select p.NAZIV, avg(OCENA*1.0) prosek, count(distinct INDEKS), max(OCENA)
from DA.PREDMET p join DA.ISPIT i on p.ID = i.IDPREDMETA and i.STATUS = 'o' and i.OCENA > 5
group by p.NAZIV, p.ID