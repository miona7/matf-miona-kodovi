with tmp as (
    select i.INDEKS, i.OZNAKAROKA, i.SKGODINA, p.NAZIV, p.ESPB, i.OCENA
    from DA.ISPIT i join DA.PREDMET p on i.IDPREDMETA = p.ID and i.STATUS = 'o' and i.OCENA > 5
    where i.POENI = p.ESPB * 6
)
select d.INDEKS, d.IME, d.PREZIME, t.NAZIV, t.ESPB, ir.NAZIV, t.OCENA
from DA.DOSIJE d join tmp t on d.INDEKS = t.INDEKS
        join DA.ISPITNIROK ir on t.OZNAKAROKA = ir.OZNAKAROKA and t.SKGODINA = ir.SKGODINA