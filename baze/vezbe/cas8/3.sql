create table DA.ISPITNIROK1 as (
    select *
    from DA.ISPITNIROK
) with data;

create view ispiti_2018 as
    select *
    from DA.ISPITNIROK1
    where SKGODINA >= 2018;

drop view ispiti_2018;

insert into ispiti_2018
values (2022, 'jan1', 'test2022', current_date - 30 days, current_date);

insert into DA.ISPITNIROK1
values (2022, 'jan2', 'test2022', current_date - 30 days, current_date);

insert into ispiti_2018
values (2015, 'xxx', 'test2022', current_date - 30 days, current_date);

update ispiti_2018
set OZNAKAROKA = 'test'
where SKGODINA = 2015 and OZNAKAROKA = 'xxx';

delete from ispiti_2018
where OZNAKAROKA = 'xxx';

select *
from ispiti_2018;

delete from ispiti_2018
where SKGODINA = 2022;

select *
from DA.ISPITNIROK1
where SKGODINA = 2015;

drop table DA.ISPITNIROK1;