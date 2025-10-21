select distinct ir.NAZIV, coalesce(dayname(i.DATPOLAGANJA), 'nije bilo ispita ili je nepoznat datum')
from DA.ISPITNIROK ir left join DA.ISPIT i on ir.OZNAKAROKA = i.OZNAKAROKA and ir.SKGODINA = i.SKGODINA
where ir.SKGODINA between 2000 and 2020