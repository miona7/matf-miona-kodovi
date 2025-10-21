select IDPREDMETA, count(distinct INDEKS)
from DA.ISPIT
group by IDPREDMETA
having count(distinct INDEKS) > 50