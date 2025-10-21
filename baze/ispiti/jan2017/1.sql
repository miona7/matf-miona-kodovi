select IME, PREZIME
from DA.DOSIJE d
where not exists(
    select *
    from DA.UPISANKURS uk join DA.PREDMETPROGRAMA pp on uk.IDPREDMETA = pp.IDPREDMETA and VRSTA = 'obavezan'
    where uk.INDEKS = d.INDEKS and not exists(
        select *
        from DA.ISPIT i
        where i.INDEKS = d.INDEKS and i.IDPREDMETA = pp.IDPREDMETA and STATUS = 'o' and OCENA >= 8
    )
) and not exists(
    select *
    from DA.ISPIT i
    where i.INDEKS = d.INDEKS and DATDIPLOMIRANJA >= current_date - 6 years and STATUS = 'o' and OCENA = 5
)