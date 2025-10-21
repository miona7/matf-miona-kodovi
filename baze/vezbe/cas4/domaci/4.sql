select ir.NAZIV
from DA.ISPITNIROK ir
where not exists(
    select *
    from DA.DOSIJE d
    where not exists(
        select *
        from DA.ISPIT i
        where i.INDEKS = d.INDEKS and i.STATUS not in ('p', 'n')
            and ir.OZNAKAROKA = i.OZNAKAROKA and ir.SKGODINA = i.SKGODINA
    ) and exists(
        select *
        from DA.ISPIT i
        where d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA = 10
    )
);


select i.OZNAKAROKA, i.SKGODINA
from DA.ISPIT i
where i.STATUS = 'o' and i.OCENA = 10
intersect
select ir.OZNAKAROKA, ir.SKGODINA
from DA.ISPITNIROK ir