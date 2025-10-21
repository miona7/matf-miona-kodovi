drop table if exists DA.DOSIJE1;

create table DA.DOSIJE1 as(
    select *
    from DA.DOSIJE
) with data;

create trigger brisanje_studenata
    before delete on DA.DOSIJE1
    referencing old as o
    for each row
        when (o.IDSTATUSA in (select ID from DA.STUDENTSKISTATUS where NAZIV = 'Diplomirao'))
        begin atomic
            signal sqlstate '75000' ('diplomirao');
        end @

insert into DA.DOSIJE1 (INDEKS, IDPROGRAMA, IME, PREZIME, IDSTATUSA, DATUPISA)
values (20220001, 103, 'Marko', 'Petrovic', -2, current date);

delete from DA.DOSIJE1
where INDEKS = 20220001;

drop trigger brisanje_studenata;