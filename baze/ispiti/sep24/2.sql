with diplomirali as (
    select d.MESTORODJENJA, count(*) broj
    from DA.DOSIJE d
    where d.DATDIPLOMIRANJA is not null
    group by d.MESTORODJENJA
), nisu_diplomirali as (
    select d.MESTORODJENJA, count(*) broj
    from DA.DOSIJE d
    where d.DATDIPLOMIRANJA is null
    group by d.MESTORODJENJA
), proseci as(
    select d.INDEKS, d.MESTORODJENJA, avg(i.OCENA * 1.0) prosek
    from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    group by d.INDEKS, d.MESTORODJENJA
    having count(*) >= 10 and avg(i.OCENA * 1.0) > 8.0
)

select d.MESTORODJENJA mesto, floor(dip.broj * 100.0 / count(*)) || '% studenata je diplomiralo' komentar
from DA.DOSIJE d join diplomirali dip on d.MESTORODJENJA = dip.MESTORODJENJA
group by d.MESTORODJENJA, dip.broj
having dip.broj > count(*) / 3

union

select d.MESTORODJENJA mesto, 'Prosek mesta je '
from DA.DOSIJE d
