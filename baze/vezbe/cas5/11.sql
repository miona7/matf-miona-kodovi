select OZNAKAROKA, count(*), count(distinct INDEKS)
from DA.ISPIT
where SKGODINA = 2016 and STATUS = 'o'
group by OZNAKAROKA, SKGODINA
having min(OCENA) > 5