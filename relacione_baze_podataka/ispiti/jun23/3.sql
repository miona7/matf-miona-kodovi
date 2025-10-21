create table stats(
    indeks integer not null primary key,
    sest smallint default 0,
    sedam smallint default 0,
    osam smallint default 0,
    devet smallint default 0,
    deset smallint default 0,
    polozeno_predmeta smallint
);

create function izracunaj_prosek(br_sestica smallint, br_sedmica smallint, br_osmica smallint, br_devetki smallint, br_desetki smallint)
returns float
return (br_sestica * 6 + br_sedmica * 7 + br_osmica * 8 + br_devetki * 9 + br_desetki * 10) * 1.0 / (br_sestica + br_sedmica + br_osmica + br_devetki + br_desetki);

insert into stats(indeks, sedam, osam)
select d.INDEKS, sum(case when i.OCENA = 7 then 1 else 0 end), sum(case when i.OCENA = 8 then 1 else 0 end)
from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID and sp.IDNIVOA = 1
                join DA.ISPIT i on i.INDEKS = d.INDEKS and i.STATUS = 'o' and i.OCENA > 5
where not exists(
    select *
    from DA.ISPIT i
    where i.INDEKS = d.INDEKS and i.STATUS = 'o' and i.OCENA = 6
)
group by d.INDEKS;

--#SET TERMINATOR @

create trigger unos
    after insert on stats
    referencing new as n
    for each row
    begin atomic
        update stats s
            set s.polozeno_predmeta = (
                select count(*)
                from DA.ISPIT i
                where i.INDEKS = n.indeks and i.STATUS = 'o' and i.OCENA > 5
                group by i.INDEKS
            ) where s.INDEKS = n.indeks;
    end @

drop table stats @

drop trigger unos @