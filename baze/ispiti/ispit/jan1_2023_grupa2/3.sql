create table student_info(
    indeks integer not null,
    mejl varchar(50),
    max_ocena smallint,
    min_ocena smallint,
    komentar varchar(40) default ''
);

create or replace function DA.mejl_adresa(indeks_arg integer)
returns varchar(50)
return
    coalesce(
        ( select upper(d.INDEKS || '.' || year(d.DATUPISA) || '.' || substr(sp.NAZIV, 1, 1) || sp.IDNIVOA ||
           '@student.matf')
        from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
        where d.INDEKS = indeks_arg) , 'Student ne postoji');

drop function DA.mejl_adresa;
values DA.mejl_adresa(20150069);

create trigger unos
    before insert on student_info
    referencing new as n
    for each row when ( n.min_ocena is null and n.max_ocena is null )
    begin
        set (n.min_ocena, n.max_ocena, n.komentar) =
            (   select min(i.OCENA), max(i.OCENA),
                       case when count(i.IDPREDMETA) < 2 then 'Student je polozio manje od dva predmeta'
                            else 'Student ima bar dve ocene' end
                from DA.ISPIT i
                where i.INDEKS = n.indeks and i.OCENA > 5 and i.STATUS = 'o'
            );
    end @

insert into student_info(indeks, mejl)
select d.INDEKS, DA.mejl_adresa(d.INDEKS)
from DA.DOSIJE d join DA.STUDENTSKISTATUS ss on d.IDSTATUSA = ss.ID
where ss.NAZIV = 'Budzet';

delete from DA.STUDENT_INFO
where MIN_OCENA = MAX_OCENA or KOMENTAR = '';

select *
from DA.STUDENT_INFO;

drop table student_info;
drop trigger unos;