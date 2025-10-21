select ESPB, ceil(ESPB * 1.2)
from DA.PREDMET
where ESPB * 1.2 > 8