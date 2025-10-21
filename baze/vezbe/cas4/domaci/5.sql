select ir.NAZIV
from DA.ISPITNIROK ir
where not exists(
    select *
    from DA.DOSIJE d
    where not exists(
        select *
        from DA.ISPIT i
        where i.INDEKS = d.INDEKS and i.STATUS = 'o' and i.OCENA = 10
            and ir.OZNAKAROKA = i.OZNAKAROKA and ir.SKGODINA = i.SKGODINA
    )
)