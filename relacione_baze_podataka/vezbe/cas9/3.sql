drop table if exists predmet_student;

create table predmet_student (
    idpredmeta integer,
    student smallint
);

insert into predmet_student
select IDPREDMETA, 5
from DA.PREDMETPROGRAMA
where IDPROGRAMA = 103 and VRSTA = 'obavezan';

merge into predmet_student
using (
    select IDPREDMETA, count(distinct INDEKS) br
    from DA.ISPIT
    where STATUS = 'o' and OCENA > 5
    group by IDPREDMETA
) as t on predmet_student.idpredmeta = t.IDPREDMETA
when matched then
    update
        set student = t.br
when not matched then
    insert
    values (t.IDPREDMETA, t.br);

select *
from predmet_student;

drop table predmet_student;