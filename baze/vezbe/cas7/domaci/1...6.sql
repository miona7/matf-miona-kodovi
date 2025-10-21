create table DA.student_ispiti (
    indeks integer not null primary key,
    broj_polozenih_ispita integer default 0,
    prosek float,
    foreign key vr_ind (indeks) references DA.DOSIJE
);

select *
from DA.student_ispiti;

drop table DA.student_ispiti;

alter table DA.student_ispiti
    add column broj_prijavljenih_ispita integer
    add constraint vr_isp check (broj_prijavljenih_ispita >= broj_polozenih_ispita);

insert into DA.student_ispiti(indeks)
    select distinct INDEKS
    from DA.ISPIT
    where STATUS = 'o';

insert into DA.student_ispiti
    select distinct d.INDEKS, NULL, NULL, NULL
    from DA.DOSIJE d
    where not exists(
        select *
        from DA.ISPIT i
        where i.INDEKS = d.INDEKS and i.STATUS = 'o'
    );

create table DA.ISPIT1 as (
    select *
    from DA.ISPIT
) with data;

update DA.ISPIT1
    set DATPOLAGANJA = (select max(DATPOLAGANJA) from DA.ISPIT1),
        OCENA = 10
where OZNAKAROKA = 'jan2' and SKGODINA = 2016;

drop table DA.ISPIT1;