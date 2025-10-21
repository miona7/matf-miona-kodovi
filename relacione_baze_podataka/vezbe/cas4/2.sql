select INDEKS
from DA.DOSIJE
where MESTORODJENJA like 'Beograd%'
intersect
select INDEKS
from DA.ISPIT
where OCENA = 10
order by INDEKS desc