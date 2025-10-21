with tmp as (
    select sp.ID smer
    from DA.STUDIJSKIPROGRAM sp join DA.DOSIJE d on d.IDPROGRAMA = sp.ID
    where d.DATDIPLOMIRANJA is not null
    group by sp.ID
    having count(*) > 5
)
select d.INDEKS, d.IME, d.PREZIME, sum(case when i.IDPREDMETA is not null then 1 else 0 end) br_prijavljenih,
       sum(case when i.STATUS = 'o' and i.OCENA > 5 then 1 else 0 end) br_polozenih,
       sum(case when i.STATUS = 'o' and i.OCENA > 5 and pp.VRSTA = 'obavezan' then 1 else 0 end) br_obaveznih
from DA.DOSIJE d left join DA.ISPIT i on i.INDEKS = d.INDEKS
    left join DA.PREDMETPROGRAMA pp on i.IDPREDMETA = pp.IDPREDMETA
where month(d.DATUPISA) = 10 and day(d.DATUPISA) between 10 and 15
    and d.DATDIPLOMIRANJA is null and d.IDPROGRAMA in (select smer from tmp)
group by d.INDEKS, d.IME, d.PREZIME
order by d.INDEKS
