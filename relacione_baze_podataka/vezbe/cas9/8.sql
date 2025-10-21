create table DA.ISPIT1 as (
    select *
    from DA.ISPIT
) with data;

create table student_polozeno(
    indeks integer not null primary key,
    espb smallint
);

create table predmet_polozeno(
    idpredmeta integer not null primary key,
    brojstudenata smallint
);

insert into student_polozeno
select d.INDEKS, sum(p.ESPB)
from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    join DA.PREDMET p on i.IDPREDMETA = p.ID
where not exists(
    select *
    from DA.PREDMETPROGRAMA pp
    where pp.IDPROGRAMA = d.IDPROGRAMA and pp.VRSTA = 'obavezan'
      and not exists(
          select *
          from DA.ISPIT i1
          where i1.INDEKS = d.INDEKS and i1.IDPREDMETA = pp.IDPREDMETA
            and i1.STATUS = 'o' and i1.OCENA > 5
    )
)
group by d.INDEKS;

merge into student_polozeno sp
using (
    select i.INDEKS indeks, sum(p.ESPB) bodovi
    from DA.ISPIT i join DA.PREDMET p on i.IDPREDMETA = p.ID and i.STATUS = 'o' and i.OCENA > 5
    group by i.INDEKS
) as t on sp.indeks = t.indeks
when matched then
    update
        set sp.espb = t.bodovi
when not matched then
    insert values (t.indeks, t.bodovi);

insert into predmet_polozeno
select IDPREDMETA, count(*)
from DA.ISPIT
where STATUS = 'o' and OCENA > 5
group by IDPREDMETA;

create trigger novi_ispit
    after insert on DA.ISPIT1
    referencing new as n
    for each row
    when (n.STATUS = 'o' and n.OCENA > 5)
         begin
            if (n.INDEKS in (select indeks from student_polozeno)) then
                update student_polozeno
                    set espb = espb + (select p.ESPB from DA.PREDMET p where n.IDPREDMETA = p.ID)
                where n.INDEKS = indeks;
            else
                insert into student_polozeno
                values (n.INDEKS, (select p.ESPB from DA.PREDMET p where n.IDPREDMETA = p.ID));
            end if;

            if(n.IDPREDMETA in (select idpredmeta from predmet_polozeno)) then
                update predmet_polozeno
                    set brojstudenata = brojstudenata + 1
                where n.IDPREDMETA = idpredmeta;
            else
                insert into predmet_polozeno
                values (n.IDPREDMETA, 1);
            end if;
         end @

select trigname
from SYSCAT.triggers;

select *
from student_polozeno
where indeks = 20150320;

select *
from predmet_polozeno
where idpredmeta = 2010;

insert into DA.ISPIT1(INDEKS, IDPREDMETA, OZNAKAROKA, SKGODINA, STATUS, POENI, OCENA)
values (20150320, 2010, 'jun2', 2017, 'o', 95, 10);

insert into DA.ISPIT1(INDEKS, IDPREDMETA, OZNAKAROKA, SKGODINA, STATUS, POENI, OCENA)
values (20152003, 1695, 'jun1', 2017, 'o', 95, 10);

select *
from student_polozeno
where indeks = 20152003;

select *
from predmet_polozeno
where idpredmeta = 1695;

drop table DA.ISPIT1;

drop table student_polozeno;

drop table predmet_polozeno;

drop trigger novi_ispit;