with tmp as (
    select ir.SKGODINA godina, ir.OZNAKAROKA oznaka, ir.NAZIV rok, p.NAZIV predmet, p.ESPB espb,
           avg(case when STATUS = 'o' and OCENA > 5 then OCENA * 1.0 else NULL end) prosek,
           sum(case when STATUS = 'o' and OCENA > 5 then 1 else 0 end) br_polozenih,
           sum(case when STATUS = 'o' and OCENA > 5 then 1 else 0 end) * 100.0 / count(*) odnos
    from DA.ISPITNIROK ir join DA.ISPIT i on ir.OZNAKAROKA = i.OZNAKAROKA and ir.SKGODINA = i.SKGODINA
                        join DA.PREDMET p on i.IDPREDMETA = p.ID
    group by ir.SKGODINA, ir.OZNAKAROKA, ir.NAZIV, p.NAZIV, p.ESPB
    order by ir.NAZIV desc
)
select rok, predmet, espb, prosek, br_polozenih, odnos
from tmp t
where odnos >= all (select odnos from tmp t1 where t.godina = t1.godina and  t.oznaka = t1.oznaka)
order by rok desc
