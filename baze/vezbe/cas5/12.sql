select INDEKS, monthname(DATPOLAGANJA) mesec, count(*) "broj predmeta"
from DA.ISPIT
where STATUS = 'o' and OCENA > 5
group by INDEKS, monthname(DATPOLAGANJA)
having count(*) > 2
order by INDEKS, mesec
