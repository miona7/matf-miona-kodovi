with najveca_ocena as (
    select IDPREDMETA predmet, max(OCENA) ocena
    from DA.ISPIT
    where STATUS = 'o' and OCENA > 5
    group by IDPREDMETA
)
select p.NAZIV, ir.NAZIV, count(*) br_polozenih
from DA.PREDMET p join DA.ISPIT i on p.ID = i.IDPREDMETA
                    join DA.ISPITNIROK ir on i.SKGODINA = ir.SKGODINA and i.OZNAKAROKA = ir.OZNAKAROKA
where STATUS = 'o' and OCENA in (select ocena from najveca_ocena where IDPREDMETA = predmet)
group by ir.SKGODINA, ir.OZNAKAROKA, p.ID, p.NAZIV, ir.NAZIV
order by p.NAZIV, br_polozenih desc, ir.NAZIV