with statistika as (
    select ir.NAZIV rok, p.NAZIV predmet, count(i.INDEKS) br_prijavljenih,
           sum(case when STATUS = 'o' and OCENA > 5 then 1 else 0 end) br_polozenih,
           sum(case when STATUS = 'x' and OCENA > 5 then 1 else 0 end ) br_ponistenih
    from DA.ISPITNIROK ir left join DA.ISPIT i on ir.SKGODINA = i.SKGODINA and ir.OZNAKAROKA = i.OZNAKAROKA
        left join DA.PREDMET p on i.IDPREDMETA = p.ID
    where i.SKGODINA between 2015 and 2019
    group by ir.NAZIV, p.NAZIV
)
select rok, predmet, br_prijavljenih, br_polozenih,
       case when br_prijavljenih > 0 then br_polozenih * 100.0 / br_prijavljenih  else 0 end procenat_polozenih,
       br_ponistenih,
       case when br_prijavljenih > 0 then br_ponistenih * 100.0 / br_prijavljenih  else 0 end procenat_ponistenih,
       case
           when br_prijavljenih > 0 and (br_polozenih + br_ponistenih) * 100.0 / br_prijavljenih > 70 then 'odlicna'
           when br_prijavljenih > 0 and (br_polozenih + br_ponistenih) * 100.0 / br_prijavljenih > 50 then 'srednja'
           else 'losa' end prolaznost
from statistika
order by prolaznost

