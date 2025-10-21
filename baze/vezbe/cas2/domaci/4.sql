select distinct p.NAZIV, i.SKGODINA, i.OZNAKAROKA
from DA.PREDMET p left join DA.ISPIT i on p.ID = i.IDPREDMETA and i.STATUS = 'x'
