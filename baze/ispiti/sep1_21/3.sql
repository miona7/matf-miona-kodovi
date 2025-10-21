create table diplomirali_stat (
    indeks integer not null primary key,
    prosek float,
    br_polozenih smallint
) ;

--# SET TERMINATOR @

create trigger diplomirali
after update of DATDIPLOMIRANJA
    on DA.DOSIJE1
referencing new as n
for each row
when ( n.DATDIPLOMIRANJA is not null and  n.INDEKS not in (select indeks from diplomirali_stat) )
begin atomic
            insert into diplomirali_stat(indeks, prosek)
                select INDEKS, avg(OCENA * 1.0)
                from DA.ISPIT i
                where STATUS = 'o' and OCENA > 5 and n.INDEKS = i.INDEKS
                group by INDEKS;
end @

update diplomirali_stat d
set br_polozenih = (
    select count(*) polozeno
    from DA.ISPIT i
    where STATUS = 'o' and OCENA > 5 and i.INDEKS = d.INDEKS
    group by INDEKS
)@


drop table  diplomirali_stat @

drop trigger diplomirali