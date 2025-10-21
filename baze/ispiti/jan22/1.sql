select d.INDEKS, IME, PREZIME, coalesce(substr(p.NAZIV, 1, 2) || substr(p.NAZIV, length(p.NAZIV) - 1), 'nema') "Kod"
from DA.DOSIJE d join DA.STUDENTSKISTATUS ss on d.IDSTATUSA = ss.ID and STUDIRA = 1
                left join DA.ISPIT i on d.INDEKS = i.INDEKS and DATPOLAGANJA >= current_date - 1 years - 6 months
                left join DA.PREDMET p on i.IDPREDMETA = p.ID
where not exists(
    select *
    from DA.ISPIT i1
    where i1.INDEKS = d.INDEKS and i1.STATUS = 'x' and i1.OCENA > 5
)
