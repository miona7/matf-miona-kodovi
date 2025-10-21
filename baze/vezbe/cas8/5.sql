create view ispiti_mm as
    select *
    from DA.ISPIT1 i
    where exists(
        select *
        from DA.DOSIJE d
        where d.IME = 'Marko' or d.IME = 'Marija'
    ) and exists(
        select *
        from DA.ISPIT1 i1
        where i1.INDEKS = i.INDEKS and i1.OZNAKAROKA = 'jan1' and i1.SKGODINA = 2018 and i1.STATUS = 'o' and i1.OCENA > 5
    ) with check option;

insert into ispiti_mm(SKGODINA, OZNAKAROKA, INDEKS, IDPREDMETA, STATUS, POENI, OCENA)
values ('2018', 'sep2', 20150013, 2027, 'o', 40, 5);

insert into ispiti_mm(SKGODINA, OZNAKAROKA, INDEKS, IDPREDMETA, STATUS, POENI, OCENA)
values ('2018', 'sep2', 20150001, 2027, 'o', 40, 5);

update ispiti_mm
    set DATPOLAGANJA = current_date
where INDEKS = 20150013 and IDPREDMETA = 2027 and SKGODINA = 2018 and OZNAKAROKA = 'sep2';

update ispiti_mm
    set DATPOLAGANJA = current_date
where INDEKS = 20150001 and IDPREDMETA = 2027 and SKGODINA = 2018 and OZNAKAROKA = 'sep2';

select *
from ispiti_mm;