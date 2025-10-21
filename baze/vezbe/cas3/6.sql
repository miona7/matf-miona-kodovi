select *
from DA.DOSIJE d
where not exists(
    select *
    from DA.SKOLSKAGODINA sk
    where not exists(
        select *
        from DA.UPISGODINE ug
        where ug.SKGODINA = sk.SKGODINA and ug.INDEKS = d.INDEKS
    )
)