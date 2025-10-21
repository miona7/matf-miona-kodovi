create table DA.DOSIJE1 as(
    select *
    from DA.DOSIJE
) with data;

select *
from DA.DOSIJE1
where INDEKS = 20171063;

update DA.DOSIJE1
    set INDEKS = 20172063
where INDEKS = 20171063;

select *
from DA.ISPIT1 i join DA.PREDMET p on i.IDPREDMETA = p.ID
where OZNAKAROKA = 'jan1' and SKGODINA = 2015 and p.NAZIV = 'Analiza 1';

create table DA.ISPIT1 as (
    select *
    from DA.ISPIT
) with data;

update DA.ISPIT1
    set OZNAKAROKA = 'jan1', DATPOLAGANJA = null
where OZNAKAROKA = 'jun1' and SKGODINA = 2015 and IDPREDMETA in (
    select ID
    from DA.PREDMET
    where NAZIV = 'Analiza 1'
);

drop table DA.DOSIJE1;

drop table DA.ISPIT1;

create table DA.PREDMET1 as(
    select *
    from DA.PREDMET
) with data;

update DA.PREDMET1
    set ESPB = (select max(ESPB) from DA.PREDMET1)
where exists(
    select i.IDPREDMETA
    from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
        and i.IDPREDMETA = ID
    where MESTORODJENJA like 'Beograd%');

select *
from DA.PREDMET1;

drop table DA.PREDMET1;

update DA.ISPIT1
set OCENA = 6
where OCENA = 5 and STATUS = 'o' and IDPREDMETA in (select ID from DA.PREDMET where NAZIV = 'Programiranje 1')