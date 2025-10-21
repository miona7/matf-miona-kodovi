create table putovanje(
    indeks integer not null primary key,
    cena integer,
    status_placanja varchar(10),
    foreign key f_indeks (indeks) references DA.DOSIJE
);

alter table putovanje
    add constraint vr_placanja check (status_placanja in ('placeno', 'oslobodjen', 'neplaceno'));

alter table putovanje
    alter column status_placanja
        set default 'neplaceno';

insert into putovanje(indeks)
select i.INDEKS
from DA.ISPIT i join DA.PREDMET p on i.IDPREDMETA = p.ID and i.STATUS = 'o'
                                         and i.OCENA > 5 and i.SKGODINA = 2016
group by i.INDEKS, i.SKGODINA
having sum(p.ESPB) * 2 >= (
        select sum(p1.ESPB)
        from DA.UPISANKURS uk join DA.PREDMET p1 on uk.IDPREDMETA = p1.ID
        where uk.INDEKS = i.INDEKS and uk.SKGODINA = i.SKGODINA
        --group by uk.INDEKS, uk.SKGODINA
    );

merge into putovanje p
using (
    select d.INDEKS indeks, count(*) * 1.0 brojpolozenih,
           sum(case when i.OCENA = 10 then 1 else 0 end) * 1.0 brojdesetki
    from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    where d.DATDIPLOMIRANJA is null
    group by d.INDEKS
) as t on p.indeks = t.indeks
when matched and t.brojdesetki * 2 >= t.brojpolozenih then
    update
        set (p.cena, p.status_placanja) = (0, 'oslobodjen')
when matched then
    update
        set p.cena = 25000 * (1 - (brojdesetki / brojpolozenih))
when not matched then
    insert(indeks, cena)
    values (t.indeks, 25000 * (1 - (brojdesetki / brojpolozenih)));

drop table putovanje;