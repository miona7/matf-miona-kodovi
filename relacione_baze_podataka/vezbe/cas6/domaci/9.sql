with tmp as (
    select i.IDPREDMETA predmet, i.OZNAKAROKA, i.SKGODINA
    from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS
    where month(d.DATUPISA) in (11, 12)
), tmp1 as (
    select i.IDPREDMETA predmet, i.OZNAKAROKA, i.SKGODINA
    from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    where month(d.DATUPISA) in (9, 10)
)
select ir.NAZIV
from DA.ISPITNIROK ir
where not exists(
    select *
    from tmp
    where tmp.OZNAKAROKA = ir.OZNAKAROKA and tmp.SKGODINA = ir.SKGODINA and not exists(
        select *
        from tmp1
        where tmp1.OZNAKAROKA = ir.OZNAKAROKA and tmp1.SKGODINA = ir.SKGODINA and tmp.predmet = tmp1.predmet
    )
)