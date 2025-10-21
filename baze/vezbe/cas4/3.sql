select INDEKS
from DA.ISPIT
where OCENA = 8
intersect
select INDEKS
from DA.ISPIT
where OCENA = 10
order by INDEKS desc