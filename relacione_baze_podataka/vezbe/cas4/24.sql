select distinct ir.NAZIV, coalesce(dayname(i.DATPOLAGANJA), 'nepoznat datum')
from DA.ISPITNIROK ir left join DA.ISPIT i on ir.OZNAKAROKA = i.OZNAKAROKA and ir.SKGODINA = i.SKGODINA
where ir.SKGODINA between 2000 and 2020
union
select ir.NAZIV, ('nije bilo ispita')
from DA.ISPITNIROK ir
where not exists(
    select *
    from DA.ISPIT i
    where i.OZNAKAROKA = ir.OZNAKAROKA and i.SKGODINA = ir.SKGODINA
) and ir.SKGODINA between 2000 and 2020
