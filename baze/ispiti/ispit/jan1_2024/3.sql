create table stats(
    mesto varchar(30) not null primary key,
    broj_studenata integer,
    broj_diplomiranih integer,
    udeo_studenata float default 0.0
);

create function DA.izracunaj_udeo(naziv_mesta varchar(30))
returns decimal(4, 2)
return
    decimal(((select count(distinct INDEKS)*1.0
    from DA.DOSIJE
    where MESTORODJENJA = naziv_mesta) / (select count(distinct INDEKS)*1.0 from DA.DOSIJE)) * 100, 4, 2);

values DA.izracunaj_udeo('Beograd');

create trigger unos
before insert on stats
referencing new as n
for each row
    begin
        set n.udeo_studenata =  DA.izracunaj_udeo(n.mesto);
    end @

insert into stats(mesto)
values ('Krusevac');

select *
from stats;

insert into stats(mesto, broj_studenata, broj_diplomiranih)
select MESTORODJENJA, count(distinct INDEKS),
       sum(case when DATDIPLOMIRANJA is not null then 1 else 0 end)
from DA.DOSIJE
where MESTORODJENJA like 'B%'
group by MESTORODJENJA;


drop table stats;
drop function DA.izracunaj_udeo;
drop trigger unos;