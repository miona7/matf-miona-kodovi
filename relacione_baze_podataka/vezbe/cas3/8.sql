select d.INDEKS
from DA.DOSIJE d
where not exists(
    select *
    from DA.ISPITNIROK ir
    where ir.OZNAKAROKA = 'jan1' and not exists(
        select *
        from DA.ISPIT i
        where d.INDEKS = i.INDEKS and i.SKGODINA = ir.SKGODINA and i.OZNAKAROKA = ir.OZNAKAROKA
            and i.STATUS not in ('p', 'n')
    )
)