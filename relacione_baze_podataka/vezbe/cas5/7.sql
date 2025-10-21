select d.INDEKS, decimal(avg(i.OCENA*1.0), 4, 2), max(i.OCENA), min(i.OCENA)
from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
where year(d.DATUPISA) = 2018
group by d.INDEKS