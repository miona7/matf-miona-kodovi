create table diplomirani(
    indeks integer not null primary key,
    polozeno_espb smallint,
    prosek float,
    datum_prvog_polozenog_ispita date
);

create table DA.DOSIJE1 as(
    select *
    from DA.DOSIJE
) with data;

create trigger unos
    before update of DATDIPLOMIRANJA on DA.DOSIJE1
    referencing old as o new as n
    for each row when (o.DATDIPLOMIRANJA is null and n.DATDIPLOMIRANJA is not null)
    begin
        insert into diplomirani
        select n.INDEKS, sum(p.ESPB), avg(i.OCENA*1.0), min(i.DATPOLAGANJA)
        from DA.ISPIT i join DA.PREDMET p on i.IDPREDMETA = p.ID and i.OCENA > 5 and i.STATUS = 'o'
        where i.INDEKS = n.INDEKS
        group by n.INDEKS;
    end;

select *
from DA.DOSIJE1
where DATDIPLOMIRANJA is null;

update DA.DOSIJE1
set DATDIPLOMIRANJA = current_date
where INDEKS = 20150109;

update DA.DOSIJE1 d
set d.DATDIPLOMIRANJA = current_date
where year(d.DATUPISA) = 2015 and exists(
    select *
    from DA.PRIZNATISPIT pi
    where pi.INDEKS = d.INDEKS
);

select *
from diplomirani;

delete from diplomirani d
where exists(
    select *
    from UPISGODINE ug join DA.STUDENTSKISTATUS ss on ug.IDSTATUSA = ss.ID
    where ug.INDEKS = d.indeks and lower(ss.NAZIV) like 'mirovanje%'
);

drop table DA.DOSIJE1;

drop table diplomirani;

drop trigger unos;