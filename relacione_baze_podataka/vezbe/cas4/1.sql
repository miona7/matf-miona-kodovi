select INDEKS
from DA.DOSIJE
where MESTORODJENJA like 'Beograd%'
union
select INDEKS
from DA.ISPIT
where OCENA = 10
order by INDEKS desc 