create table diplomirali_stat(
    indeks integer not null primary key,
    prosek float,
    br_polozenih smallint
);

create table DA.DOSIJE1 as(
    select *
    from DA.DOSIJE
) with data;

create trigger diplomirali
    after update of DATDIPLOMIRANJA on DA.DOSIJE1
    referencing new as n
    for each row when (n.DATDIPLOMIRANJA is not null
        and n.INDEKS not in (select indeks from diplomirali_stat))
    begin
            insert into diplomirali_stat(indeks, prosek)
            select n.INDEKS, avg(i.OCENA*1.0)
            from DA.ISPIT i
            where i.INDEKS = n.INDEKS and i.STATUS = 'o' and i.OCENA > 5
            group by n.INDEKS;
    end;

select *
from diplomirali_stat;

update DA.DOSIJE1
set DATDIPLOMIRANJA = current_date
where INDEKS = 20150090;

delete from diplomirali_stat;

merge into diplomirali_stat ds
using (
    select i.INDEKS student, count(*) br_pol
    from DA.ISPIT i
    where i.STATUS = 'o' and i.OCENA > 5
    group by i.INDEKS
) as t on ds.indeks = t.student
when matched then
    update set ds.br_polozenih = t.br_pol;


drop table diplomirali_stat;

drop trigger diplomirali;

drop table DA.DOSIJE1;