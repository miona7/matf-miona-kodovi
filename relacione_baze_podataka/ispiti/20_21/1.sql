select d.INDEKS, IME, PREZIME, 'm' || lower(sp.OZNAKA) || substr(d.INDEKS, 3) || '@stud.matf.bg.ac.rs' "E-adresa"
from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
where not exists(
        select *
        from DA.UPISANKURS uk join DA.PREDMETPROGRAMA pp on uk.IDPREDMETA = pp.IDPREDMETA
            and pp.IDPROGRAMA = sp.ID and VRSTA = 'obavezan'
        where uk.INDEKS = d.INDEKS and not exists(
            select *
            from DA.ISPIT i
            where i.INDEKS = d.INDEKS and i.IDPREDMETA = pp.IDPREDMETA and STATUS = 'o' and OCENA >= 8
        )
    ) and not exists(
        select *
        from DA.ISPIT i1
        where i1.INDEKS = d.INDEKS and DATPOLAGANJA >= current_date - 6 year and STATUS = 'o' and OCENA = 5
)