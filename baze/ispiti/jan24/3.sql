create table stats (
    mesto char(30) not null primary key,
    broj_studenata int,
    broj_diplomiranih int,
    udeo_studenata float default 0
)@

select *
from DOSIJE;

create function izracunaj_udeo(mesto char(30))
returns float
return
    select decimal((select count(*) from DOSIJE where MESTORODJENJA = mesto) * 100.0 / count(*) * 1.0, 4, 2)
    from DOSIJE @

drop function izracunaj_udeo @

values izracunaj_udeo('Krusevac');

create trigger unos
    before insert on stats
    referencing new as n
    for each row
    begin atomic
        set n.udeo_studenata = izracunaj_udeo(n.mesto);
    end @

insert into stats(mesto)
select distinct MESTORODJENJA
from DA.DOSIJE
where MESTORODJENJA like 'B%' @


select *
from stats @

drop table stats @
drop function izracunaj_udeo @
drop trigger unos @