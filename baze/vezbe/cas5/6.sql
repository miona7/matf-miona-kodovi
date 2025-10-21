select OZNAKA, NAZIV, ESPB
from DA.PREDMET
where ESPB > (select avg(p.ESPB) from DA.PREDMET p)