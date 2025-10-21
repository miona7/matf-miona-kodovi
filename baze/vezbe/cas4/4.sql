select INDEKS
from DA.DOSIJE
where MESTORODJENJA like 'Beograd%'
except
select INDEKS
from DA.ISPIT
where OCENA = 10
order by INDEKS desc