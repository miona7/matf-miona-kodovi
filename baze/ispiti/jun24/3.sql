create table apsolvent(
    indeks integer not null primary key,
    poenadokraja smallint,
    godinastudija smallint,
    vremeunosa date default current_date
);

create function is_polozeno(student integer, predmet smallint)
returns smallint
return
    case when exists(
            select *
            from DA.ISPIT i
            where i.INDEKS = student and i.IDPREDMETA = predmet and i.STATUS = 'o' and i.OCENA > 5
        ) then 1
        else 0 end;

insert into apsolvent(indeks, poenadokraja, godinastudija)
select d.INDEKS, sp.OBIMESPB - sum(p.ESPB), year(current_date) - year(d.DATUPISA)
from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
        join DA.ISPIT i on i.INDEKS = d.INDEKS and i.STATUS = 'o' and i.OCENA > 5
        join DA.PREDMET p on p.ID = i.IDPREDMETA
where d.DATDIPLOMIRANJA is null
group by d.INDEKS, sp.OBIMESPB, d.DATUPISA
having sp.OBIMESPB - sum(p.ESPB) < 30;

--# SET TERMINATOR @

create trigger unos_ispita
    after insert on DA.ISPIT
    referencing new as n
    for each row
    when (n.INDEKS in (select indeks from apsolvent))
         begin atomic
            update apsolvent a
                set a.poenadokraja = a.poenadokraja - (
                    select p.ESPB
                    from DA.PREDMET p
                    where p.ID = n.IDPREDMETA
                ) where a.indeks = n.INDEKS;
         end @

select *
from apsolvent @

select ESPB
from DA.PREDMET
where ID = 2352 @

insert into DA.ISPIT(INDEKS, OCENA, POENI, IDPREDMETA, STATUS, SKGODINA, OZNAKAROKA)
values (20160370, 10, 100, 2352, 'o', 2019, 'jan1') @


delete from apsolvent
where poenadokraja <= 0 @

drop table apsolvent @

drop trigger unos_ispita @