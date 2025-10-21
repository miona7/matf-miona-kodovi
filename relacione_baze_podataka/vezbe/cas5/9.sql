select count(INDEKS)
from DA.PREDMET p left join DA.ISPIT i on p.ID = i.IDPREDMETA and i.STATUS = 'o' and i.OCENA > 5
group by p.ID