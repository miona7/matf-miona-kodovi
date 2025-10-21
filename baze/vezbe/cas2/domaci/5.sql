select distinct p.NAZIV, ir.NAZIV
from DA.PREDMET p left join DA.ISPIT i on p.ID = i.IDPREDMETA and i.STATUS = 'x'
    left join DA.ISPITNIROK ir on i.SKGODINA = ir.SKGODINA and i.OZNAKAROKA = ir.OZNAKAROKA
