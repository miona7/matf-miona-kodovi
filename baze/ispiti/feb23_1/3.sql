create table student_mentor(
    student integer not null primary key,
    mentor integer,
    datpocetka date,
    komentar varchar(200),
    foreign key fk (mentor) references DA.DOSIJE
);

create function generisi_komentar(indeksARG integer)
returns varchar(200)
return
    case when indeksARG in (
        select INDEKS
        from DA.DOSIJE
        where DATDIPLOMIRANJA is not null
    )  then (
        select d.IME || ' ' || d.PREZIME || ' je diplomirao sa prosekom ' || avg(OCENA * 1.0)
        from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and STATUS = 'o' and OCENA > 5
        where d.INDEKS = indeksARG
        group by d.INDEKS, d.IME, d.PREZIME
    ) else 'Student ne postoji ili nije diplomirao' end;


insert into student_mentor(student, mentor, datpocetka)
with mentor as(
    select sp.ID, sp.NAZIV, min(d.INDEKS) indeks
    from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
    where d.DATDIPLOMIRANJA is not null and sp.IDNIVOA = 2
    group by sp.ID, sp.NAZIV
)
select d.INDEKS, m.indeks, current_date - 1 day
from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
    join mentor m on m.NAZIV = sp.NAZIV
where d.DATDIPLOMIRANJA is null and sp.IDNIVOA = 1;

merge into student_mentor sm
using (
    select d1.INDEKS student, d1.DATUPISA, max(d2.INDEKS) mentor
    from DA.DOSIJE d1 join DA.DOSIJE d2 on d2.IDPROGRAMA = d1.IDPROGRAMA and d1.INDEKS < d2.INDEKS
        and d1.MESTORODJENJA = d2.MESTORODJENJA
    where d1.DATDIPLOMIRANJA is null and d2.DATDIPLOMIRANJA is not null
    group by d1.INDEKS, d1.DATUPISA
) as tmp on sm.student = tmp.student
when matched then
    update
    set sm.komentar = generisi_komentar(tmp.mentor)
when matched and sm.mentor is null then
    update
    set sm.mentor = tmp.mentor and sm.datpocetka = tmp.DATUPISA + 7 days;


delete from student_mentor
where datpocetka is null or datpocetka < current_date - 3 years;

drop table student_mentor;