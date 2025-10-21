select p.NAZIV, d.IME, d.PREZIME, current_date - d.DATDIPLOMIRANJA "vreme od diplomiranja"
from DA.DOSIJE d join DA.PREDMETPROGRAMA pp on d.IDPROGRAMA = pp.IDPROGRAMA and pp.VRSTA = 'izborni'
                join DA.PREDMET p on pp.IDPREDMETA = p.ID
where d.DATDIPLOMIRANJA is not null and DATDIPLOMIRANJA >= current_date - 5 years - 6 months
    and length(d.PREZIME) in (5, 8, 10) and exists(
        select *
        from DA.ISPIT i
        where i.INDEKS = d.INDEKS and i.STATUS = 'o' and i.IDPREDMETA = p.ID
)
