with max_ocena_predmeta as(
    select i.IDPREDMETA predmet, max(i.OCENA) ocena
    from DA.ISPIT i
    where i.STATUS = 'o' and i.OCENA > 5
    group by i.IDPREDMETA
)
select p.NAZIV, ir.NAZIV, count(*) br_ispita
from DA.PREDMET p join DA.ISPIT i on p.ID = i.IDPREDMETA
    join DA.ISPITNIROK ir on i.OZNAKAROKA = ir.OZNAKAROKA and i.SKGODINA = ir.SKGODINA
where i.STATUS = 'o' and i.OCENA = (select mop.ocena from max_ocena_predmeta mop where mop.predmet = p.ID)
group by p.ID, ir.OZNAKAROKA, ir.SKGODINA, p.NAZIV, ir.NAZIV
order by p.NAZIV, br_ispita desc, ir.NAZIV