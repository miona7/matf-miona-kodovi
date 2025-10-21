select d.INDEKS, d.IME, d.PREZIME, count(*) "broj prijavljenih ispita",
       count(distinct p.ID) "broj prijavljenih predmeta",
       sum(case when i.STATUS = 'o' and i.OCENA > 5 then 1 else 0 end) "broj polozenih ispita",
       avg(case when i.STATUS = 'o' and i.OCENA > 5 then OCENA*1.0 else NULL end) prosek
from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS join DA.PREDMET p on i.IDPREDMETA = p.ID
where lower(d.IME) like '%o%' or lower(d.IME) like '%a%'
group by d.INDEKS, d.IME, d.PREZIME
having sum(case when i.STATUS = 'o' and i.OCENA > 5 then p.ESPB else 0 end) between 15 and 25
order by d.INDEKS