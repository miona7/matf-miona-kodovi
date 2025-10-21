select NAZIV, ESPB * 2000 "cena predmeta u dinarima"
from DA.PREDMET
where ESPB * 2000 > 10000