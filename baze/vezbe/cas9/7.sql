create table broj_predmeta(
    broj smallint
);

create table DA.PREDMET1 as (
    select *
    from DA.PREDMET
) with data;

insert into broj_predmeta
select count(*)
from DA.PREDMET1;

select *
from broj_predmeta;

create trigger azuriraj_broj_predmeta
    after insert on DA.PREDMET1
    for each row
        begin
            update broj_predmeta
                set broj = broj + 1;
        end @

insert into DA.PREDMET1(ID, OZNAKA, NAZIV, ESPB)
values (5000, 'X', 'X', 4);

create trigger az_br_pr
    after delete on DA.PREDMET1
    for each row
        begin
            update broj_predmeta
                set broj = broj - 1;
        end @

delete from DA.PREDMET1 where ID = 5000;

drop trigger azuriraj_broj_predmeta;

drop table broj_predmeta;

drop table DA.PREDMET1;

drop trigger az_br_pr;

SELECT TRIGNAME
FROM SYSCAT.TRIGGERS
ORDER BY TABSCHEMA, TABNAME, TRIGNAME;