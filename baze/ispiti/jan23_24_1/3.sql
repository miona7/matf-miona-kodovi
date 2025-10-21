create table student_info (
    indeks int not null primary key ,
    mejl varchar(40),
    max_ocena smallint,
    min_ocena smallint,
    aritmeticka_sredina float default 5.0
) @

create function mejl_adresa(indeks INTEGER)
returns varchar(40)
return
    select lower(IME || '.' || PREZIME || '.' || substr(sp.NAZIV, 1, 1) || IDNIVOA || '@student.matf')
    from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
    where d.INDEKS = indeks @

create trigger unos_student_info
    before insert on student_info
    referencing new as n
    for each row
    when (n.min_ocena is null and n.max_ocena is null)
         begin atomic
            set min_ocena = (select min(OCENA) from DA.ISPIT i where i.INDEKS = n.indeks and STATUS = 'o' and OCENA > 5);
            set max_ocena = (select max(OCENA) from DA.ISPIT i where i.INDEKS = n.indeks and STATUS = 'o' and OCENA > 5);
            set aritmeticka_sredina = (min_ocena + max_ocena) / 2.0;
         end @


insert into student_info(indeks, mejl)
select INDEKS, mejl_adresa(INDEKS)
from DA.DOSIJE d join DA.STUDENTSKISTATUS ss on d.IDSTATUSA = ss.ID
where NAZIV = 'Samofinansiranje' @

delete from student_info si
where si.min_ocena = si.max_ocena or si.aritmeticka_sredina is null;