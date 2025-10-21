select distinct ir.NAZIV, i.OCENA
from DA.ISPITNIROK ir left join DA.ISPIT i on ir.SKGODINA = i.SKGODINA and ir.OZNAKAROKA = i.OZNAKAROKA
    and i.STATUS = 'o' and i.OCENA > 5
order by ir.NAZIV, i.OCENA desc