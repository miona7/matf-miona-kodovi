select *
from DA.PREDMET
where ESPB = (select max(ESPB) from DA.PREDMET)