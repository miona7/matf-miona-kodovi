create table student_info(
    indeks integer not null primary key,
    mejl varchar(50),
    max_ocena smallint,
    min_ocena smallint,
    aritmeticka_sredina float default 5.0
);

create or replace function DA.mejl_adresa(indeks_arg integer)
returns varchar(50)
return
    coalesce((select lower(d.IME || '.' || d.PREZIME || '.' || substr(sp.NAZIV, 1, 1)
               || sp.IDNIVOA || '@student.matf')
    from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
    where d.INDEKS = indeks_arg), 'Student ne postoji...');

create trigger unos
before insert on student_info
referencing new as n
for each row when ( n.min_ocena is null and n.max_ocena is null )
    begin
        set (n.min_ocena, n.max_ocena, n.aritmeticka_sredina) = (
        select min(i.OCENA), max(i.OCENA), (min(i.OCENA) + max(i.OCENA)) * 1.0 / 2.0
        from DA.ISPIT i
        where i.INDEKS = n.indeks and i.OCENA > 5 and i.STATUS = 'o'
        );
    end @

insert into student_info(indeks, mejl)
select d.INDEKS, DA.mejl_adresa(d.INDEKS)
from DA.DOSIJE d join DA.STUDENTSKISTATUS ss on d.IDSTATUSA = ss.ID
where ss.NAZIV = 'Samofinansiranje';

select *
from student_info;

delete from student_info
where min_ocena = max_ocena or aritmeticka_sredina is null;

drop table student_info;
drop function DA.mejl_adresa;
drop trigger unos;