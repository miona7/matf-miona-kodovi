with najkraceStudira as (
    select min(current_date - DATUPISA) vreme
    from DA.DOSIJE
)
select d.INDEKS, d.IME, d.PREZIME, coalesce(p.NAZIV, repeat('*', length(d.PREZIME)))
from DA.DOSIJE d left join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    left join DA.PREDMET p on i.IDPREDMETA = p.ID
where current_date - d.DATUPISA = (select vreme from najkraceStudira)
group by d.INDEKS, d.IME, d.PREZIME, p.NAZIV
