create table DA.ISPIT1 as (
    select *
    from DA.ISPIT
) with data;

create view ispiti_marka_petrovica as
    select i.*
    from DA.ISPIT1 i join DA.DOSIJE d on i.INDEKS = d.INDEKS
    where d.IME = 'Marko' and d.PREZIME = 'Petrovic';

update ispiti_marka_petrovica
    set DATPOLAGANJA = null;
--- javlja gresku ne sme join

create view ispiti_marka_petrovica as
    select i.*
    from DA.ISPIT1 i
    where exists(
        select *
        from DA.DOSIJE d
        where d.IME = 'Marko' and d.PREZIME = 'Petrovic' and i.INDEKS = d.INDEKS);

update ispiti_marka_petrovica
    set DATPOLAGANJA = null;

drop view ispiti_marka_petrovica;
