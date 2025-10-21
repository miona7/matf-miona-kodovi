with tmp as (
    select d.INDEKS, count(*) br_polozenih
    from DA.DOSIJE d join DA.ISPIT i on i.INDEKS = d.INDEKS and i.STATUS = 'o'
    where i.DATPOLAGANJA >= current_date - 6 years and (i.OCENA = 9 or i.OCENA = 10)
    group by d.INDEKS
    having count(*) >= 3
)
select d.IME || ' ' || d.PREZIME, p.NAZIV, coalesce(monthname(d.DATDIPLOMIRANJA), 'Nije diplomirao')
from DA.DOSIJE d left join DA.UPISANKURS uk on d.INDEKS = uk.INDEKS
                    left join DA.PREDMET p on uk.IDPREDMETA = p.ID
where not exists(
    select *
    from DA.ISPIT i
    where i.INDEKS = d.INDEKS and i.IDPREDMETA = p.ID and i.STATUS = 'o' and i.OCENA > 5
) and d.INDEKS in (select t.INDEKS from tmp t)
group by p.ID, d.IME, d.PREZIME, p.NAZIV, d.DATDIPLOMIRANJA
order by d.IME, d.PREZIME, p.NAZIV desc