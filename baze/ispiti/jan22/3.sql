create table diplomirani(
    indeks integer not null primary key,
    polozeno_espb smallint,
    prosek float,
    datum_prvog_polozenog_ispita date
) @

--# SET TERMINATOR @

drop trigger unos @

create trigger unos
    before update of DATDIPLOMIRANJA on DA.DOSIJE1
    referencing new as n
        old as o
    for each row
    when (n.DATDIPLOMIRANJA is not null and o.DATDIPLOMIRANJA is null)
    begin
        insert into diplomirani
        select n.INDEKS, sum(ESPB), avg(OCENA * 1.0), min(DATPOLAGANJA)
        from DA.ISPIT i join DA.PREDMET p on i.IDPREDMETA = p.ID
        where i.INDEKS = n.INDEKS and STATUS = 'o' and OCENA > 5
        group by n.INDEKS;
    end @


create table DOSIJE1 as (
    select *
    from DA.DOSIJE
) with data @


update DOSIJE1 d
set DATDIPLOMIRANJA = current_date
where year(DATUPISA) = 2015 and INDEKS in (
    select INDEKS
    from DA.PRIZNATISPIT i
)
@

delete from diplomirani
where indeks in (select indeks
from DA.UPISGODINE ug join DA.STUDENTSKISTATUS ss on ug.IDSTATUSA = ss.ID
where lower(ss.NAZIV) like 'mirovanje%')
@

drop table diplomirani @

select *
from diplomirani