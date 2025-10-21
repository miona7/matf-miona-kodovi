select d.INDEKS, d.IME, d.PREZIME, p.NAZIV, i.OZNAKAROKA, i.SKGODINA
from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    join DA.PREDMET p on i.IDPREDMETA = p.ID
where exists(
    select *
    from DA.ISPIT i1
    where i1.INDEKS = d.INDEKS and i1.SKGODINA = 2018 and i1.STATUS not in ('p', 'n')
)
