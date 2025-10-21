with tmp as(
    select ir.OZNAKAROKA oznakaroka, ir.SKGODINA skgodina, ir.NAZIV rok, p.NAZIV predmet, p.ESPB espb,
           avg(case when i.OCENA > 5 and i.STATUS = 'o' then i.OCENA * 1.0 else null end) prosek,
            count(case when i.OCENA > 5 and i.STATUS = 'o' then 1 else null end) polozeno,
             count(case when i.OCENA > 5 and i.STATUS = 'o' then 1 else null end) * 100.0 / count(*) procenat
    from DA.ISPITNIROK ir join DA.ISPIT i on ir.OZNAKAROKA = i.OZNAKAROKA and ir.SKGODINA = i.SKGODINA
    join DA.PREDMET p on p.ID = i.IDPREDMETA
    group by ir.SKGODINA, ir.OZNAKAROKA, ir.NAZIV, p.NAZIV, p.ESPB
    order by ir.NAZIV
)
select t.rok, predmet, espb, prosek, polozeno, procenat
from tmp t
where t.procenat = (
    select max(t1.procenat)
    from tmp t1
    where t.oznakaroka = t1.oznakaroka and t.skgodina = t1.skgodina
)
order by t.rok desc