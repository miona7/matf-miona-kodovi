create table predmet_stat (
    id integer not null primary key,
    prijavilo smallint,
    polozilo smallint,
    prosek float
);

insert into predmet_stat(id, prijavilo, polozilo)
select pp.IDPREDMETA, sum(case when STATUS = 'p' then 1 else 0 end),
                        sum(case when STATUS = 'o' and OCENA > 5 then 1 else 0 end)
from PREDMETPROGRAMA pp join DA.ISPIT i on pp.IDPREDMETA = i.IDPREDMETA
where VRSTA = 'obavezan'
group by pp.IDPREDMETA;

merge into predmet_stat ps
using (
    select distinct pp.IDPREDMETA predmet, VRSTA, sum(case when STATUS = 'p' then 1 else 0 end) prijavilo,
                        sum(case when STATUS = 'o' and OCENA > 5 then 1 else 0 end) polozilo,
                        avg(case when STATUS = 'o' and OCENA > 5 then OCENA * 1.0 else 0.0 end) prosek
    from PREDMETPROGRAMA pp join DA.ISPIT i on pp.IDPREDMETA = i.IDPREDMETA
    group by pp.IDPREDMETA, VRSTA
) as tmp
on ps.id = tmp.predmet
when matched and tmp.VRSTA = 'obavezan' then
    update
    set prijavilo = tmp.prijavilo
when matched and tmp.VRSTA = 'izborni' then
    update
    set polozilo = tmp.polozilo
when not matched then
    insert (id, prijavilo, polozilo, prosek)
    values (tmp.predmet, tmp.prijavilo, tmp.polozilo, tmp.prosek);

drop table predmet_stat;
