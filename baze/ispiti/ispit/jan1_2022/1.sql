select d.INDEKS, d.IME, d.PREZIME,
       coalesce(substr(p.NAZIV, 1, 2) || substr(p.NAZIV, length(p.NAZIV) - 1), 'nema') "Kod"
from DA.DOSIJE d join DA.STUDENTSKISTATUS ss on d.IDSTATUSA = ss.ID and ss.STUDIRA = 1
    left join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
                                and i.DATPOLAGANJA >= current_date - 5 years - 6 months
    left join DA.PREDMET p on i.IDPREDMETA = p.ID
where not exists(
    select *
    from DA.ISPIT i1
    where i1.INDEKS = d.INDEKS and i1.STATUS = 'x'
)
order by d.INDEKS