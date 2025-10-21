select p.NAZIV, i.SKGODINA, max(i.OCENA)
from DA.ISPIT i join DA.PREDMET p on i.IDPREDMETA = p.ID
group by p.NAZIV, p.ID, i.SKGODINA