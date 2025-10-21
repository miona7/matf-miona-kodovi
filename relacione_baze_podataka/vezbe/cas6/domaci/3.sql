
with brojPolaganjaJedan as (
    select distinct i.IDPREDMETA predmet
    from DA.ISPIT i
    where i.STATUS not in ('p', 'n') and not exists(
        select *
        from DA.ISPIT i2
        where i2.IDPREDMETA = i.IDPREDMETA and (i.OZNAKAROKA <> i2.OZNAKAROKA or i.SKGODINA <> i2.SKGODINA)
    )
)
select ir.NAZIV, d.INDEKS, IME, PREZIME, p.NAZIV
from DA.PREDMET p join DA.ISPIT i on i.IDPREDMETA = p.ID join DA.ISPITNIROK ir
                    on ir.OZNAKAROKA = i.OZNAKAROKA and ir.SKGODINA = i.SKGODINA
                    join DA.DOSIJE d on d.INDEKS = i.INDEKS
where p.ID in (select predmet from brojPolaganjaJedan)
order by p.ID