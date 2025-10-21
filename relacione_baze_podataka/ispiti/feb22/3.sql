create table ispitni_rok_stat(
    oznakaroka varchar(20) not null,
    skgodina smallint not null,
    brpredmeta smallint,
    prosek float,
    primary key (oznakaroka, skgodina)
);

select *
from ispitni_rok_stat;

insert into ispitni_rok_stat(oznakaroka, skgodina, brpredmeta)
select ir.OZNAKAROKA, ir.SKGODINA, count(distinct i.IDPREDMETA)
from DA.ISPITNIROK ir join DA.ISPIT i on ir.SKGODINA = i.SKGODINA and ir.OZNAKAROKA = i.OZNAKAROKA
where i.STATUS = 'o'
group by ir.SKGODINA, ir.OZNAKAROKA
having count(distinct i.IDPREDMETA) * 4 >= (select count(*) from DA.PREDMET);

merge into ispitni_rok_stat irs
using (
    select ir.OZNAKAROKA oznakaroka, ir.SKGODINA skgodina, count(distinct i.IDPREDMETA) brpredmeta,
        avg(case when i.OCENA > 5 then i.OCENA * 1.0 else null end) prosek
    from DA.ISPITNIROK ir join DA.ISPIT i on ir.SKGODINA = i.SKGODINA and ir.OZNAKAROKA = i.OZNAKAROKA
    where i.STATUS = 'o'
    group by ir.SKGODINA, ir.OZNAKAROKA
) t on t.oznakaroka = irs.oznakaroka and t.skgodina = irs.skgodina
when matched and t.skgodina >= 2019 then
    update
    set irs.prosek = t.prosek
when matched and t.skgodina < 2019 then
    update
    set irs.brpredmeta = t.brpredmeta
when not matched then
    insert
    values (t.oznakaroka, t.skgodina, t.brpredmeta, t.prosek);

delete from ispitni_rok_stat irs
where irs.oznakaroka = 'kom' or exists(
    select *
    from DA.ISPIT i
    where i.SKGODINA = irs.skgodina and i.OZNAKAROKA = irs.oznakaroka and i.STATUS = 'd'
);

drop table ispitni_rok_stat;