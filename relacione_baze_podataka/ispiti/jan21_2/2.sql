with tmp as (
    select pp.IDPREDMETA
    from DA.PREDMETPROGRAMA pp join DA.STUDIJSKIPROGRAM sp on pp.IDPROGRAMA = sp.ID
        join DA.PREDMET p on p.ID = pp.IDPREDMETA
    where pp.VRSTA = 'izborni'
    group by pp.IDPREDMETA
    having count(*) > 2
)
select p.NAZIV, count(i.INDEKS) br_prijavljenih,
       avg(case when i.STATUS = 'o' and i.OCENA > 5 then OCENA * 1.0 else null end) prosek,
       sum(case when i.STATUS = 'o' and i.OCENA = 10 and d.MESTORODJENJA = 'Novi Sad' then 1 else 0 end) broj
from DA.PREDMET p left join DA.ISPIT i on p.ID = i.IDPREDMETA
                    left join DA.DOSIJE d on d.INDEKS = i.INDEKS
where length(p.NAZIV) - length(replace(p.NAZIV, ' ', '')) >= 2 and p.ID in (select tmp.IDPREDMETA from tmp)
group by p.ID, p.NAZIV
order by p.NAZIV