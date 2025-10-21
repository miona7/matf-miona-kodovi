with godine as (
    select d.IME, d.INDEKS, count(*) god
    from DA.DOSIJE d join DA.UPISGODINE ug on d.INDEKS = ug.INDEKS
    group by d.IME, d.INDEKS
)
select d.IME, decimal(avg(god * 1.0), 5, 3) prosek, days(current_date) - days(DATPOLAGANJA) dani
from DA.DOSIJE d join godine g on d.INDEKS = g.INDEKS
                join DA.ISPIT i on d.INDEKS = i.INDEKS and STATUS = 'o' and OCENA > 5
group by d.IME, DATPOLAGANJA
having min(DATPOLAGANJA)