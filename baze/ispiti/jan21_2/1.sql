select p.NAZIV, d.IME, d.PREZIME, current_date - d.DATUPISA "Period studiranja"
from DA.DOSIJE d join DA.PREDMETPROGRAMA pp on d.IDPROGRAMA = pp.IDPROGRAMA and pp.VRSTA = 'obavezan'
                join DA.PREDMET p on pp.IDPREDMETA = p.ID
where d.DATDIPLOMIRANJA is null and year(current_date) - year(d.DATUPISA) < 6 and length(d.IME) between 4 and 10
    and exists(
        select *
        from DA.ISPIT i
        where i.INDEKS = d.INDEKS and i.IDPREDMETA = p.ID and STATUS = 'o'
)