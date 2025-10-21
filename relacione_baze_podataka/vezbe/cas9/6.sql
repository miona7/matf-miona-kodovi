drop table DA.PREDMET1 if exists;

create table DA.PREDMET1 as (
    select *
    from DA.PREDMET
) with data;

create trigger azuriranje_espb
    before update of ESPB on DA.PREDMET1
    referencing
        old as o
        new as n
    for each row
        begin
            set n.ESPB =
                case
                    when n.ESPB > o.ESPB then o.ESPB + 1
                    when n.ESPB < o.ESPB then o.ESPB - 1
                end;
        end @

insert into DA.PREDMET1(ID, OZNAKA, NAZIV, ESPB)
values (5000, 'X', 'X', 4);

update DA.PREDMET1
set ESPB = 10
where ID = 5000;

select *
from DA.PREDMET1
where ID = 5000;

delete
from DA.PREDMET1
where ID = 5000;

update DA.PREDMET1
set ESPB = 1
where ID = 5000;

drop trigger azuriranje_espb;