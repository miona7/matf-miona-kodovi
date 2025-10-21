create table DOSIJE1 as (
    select *
    from DA.DOSIJE
) with data;

drop view p;

create view p as
    select d.INDEKS, d.IDPROGRAMA, d.IME, d.PREZIME, d.IDSTATUSA, d.DATUPISA
    from DA.DOSIJE1 d
    where exists(
        select *
        from DA.ISPIT i
        where i.INDEKS = d.INDEKS and i.STATUS = 'o' and i.OCENA = 10
    ) with check option;

select *
from p;

select *
from DA.DOSIJE1 d;

insert into p
values (20150002,101,'Filip','Jevtovic', 2, current_date);

drop table DA.DOSIJE1;

drop view p;