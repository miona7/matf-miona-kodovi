create table DA.PREDMET1 as (
    select *
    from DA.PREDMET
) with data;

create trigger zabrana_brisanja
    before delete on DA.PREDMET1
    referencing old as o
    for each row
    when (o.ESPB > 15)
         begin atomic
             signal sqlstate '75000' ('ne');
         end @

select *
from DA.PREDMET1
where ESPB > 15;

delete from DA.PREDMET1
where ID = 1650;

drop table DA.PREDMET1;

drop trigger zabrana_brisanja;


select trigname
from SYSCAT.triggers;