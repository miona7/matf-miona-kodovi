select distinct ir.NAZIV, p.NAZIV, decimal(avg(i.OCENA*1.0), 4, 2)
from DA.ISPITNIROK ir join DA.ISPIT i on ir.OZNAKAROKA = i.OZNAKAROKA and ir.SKGODINA = i.SKGODINA
    join DA.PREDMET p on i.IDPREDMETA = p.ID and i.STATUS = 'o' and i.OCENA > 5
group by ir.NAZIV, ir.OZNAKAROKA, ir.SKGODINA, p.NAZIV, p.ID
having decimal(avg(i.OCENA*1.0), 4, 2) >= all (
    select decimal(avg(i1.OCENA*1.0), 4, 2)
    from DA.ISPIT i1
    where i1.OZNAKAROKA = ir.OZNAKAROKA and i1.SKGODINA = ir.SKGODINA and i1.STATUS = 'o' and i1.OCENA > 5
    group by i1.IDPREDMETA
)
order by ir.NAZIV