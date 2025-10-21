select count(*) "broj predmeta", sum(p.ESPB) "broj espb"
from DA.ISPIT i join DA.PREDMET p on i.IDPREDMETA = p.ID and i.STATUS = 'o' and i.OCENA > 5
where i.INDEKS = 20160025