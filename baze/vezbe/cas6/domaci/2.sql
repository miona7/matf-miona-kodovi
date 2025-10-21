with polaganja as (
    select i1.INDEKS student, i1.IDPREDMETA id, days_between(i2.DATPOLAGANJA, i1.DATPOLAGANJA) razlika
    from DA.ISPIT i1 join DA.ISPIT i2 on i1.IDPREDMETA = i2.IDPREDMETA and i1.INDEKS = i2.INDEKS
        and i2.DATPOLAGANJA > i1.DATPOLAGANJA
    where days_between(i2.DATPOLAGANJA, i1.DATPOLAGANJA) <= 20
)
select p.NAZIV, pl.student, pl.razlika
from DA.PREDMET p join polaganja pl on p.ID = pl.id
where p.NAZIV like '___gr%' and p.ESPB between 5 and 10
order by p.ID