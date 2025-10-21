create table mentor_master (
    indeks integer not null,
    idpredmeta integer not null,
    ocena smallint,
    primary key (indeks, idpredmeta),
    constraint vr_ocena check (ocena in (9, 10))
);

create view master_studenti as
    select d.INDEKS
    from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID and sp.IDNIVOA = 2
                    join DA.STUDENTSKISTATUS ss on d.IDSTATUSA = ss.ID and ss.STUDIRA = 1;

--# SET TERMINATOR @

create trigger master_ispit
    after insert on DA.ISPIT
    referencing new as n
    for each row
    when (n.OCENA > 8 and n.INDEKS in (select m.INDEKS from master_studenti m)
            and n.POENI = (
                select max(i.POENI)
                from DA.ISPIT i
                where i.INDEKS = n.INDEKS and i.STATUS = 'o' and i.OCENA > 5))
    begin atomic
        insert into mentor_master
        values (n.INDEKS, n.IDPREDMETA, n.OCENA);
    end @

drop table mentor_master @
drop trigger master_ispit @
drop view master_studenti @

insert into DA.ISPIT(SKGODINA, OZNAKAROKA, INDEKS, IDPREDMETA, STATUS, POENI, OCENA)
values (2019, 'sep4', 20161126, 2301, 'o', 100, 10)
@

select *
from mentor_master @

select *
from SYSCAT.VIEWS
where OWNERTYPE = 'U' @
