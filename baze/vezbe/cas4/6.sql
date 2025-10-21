select NAZIV, ESPB, case when ESPB > 15 then 'I kategorija'
                        when ESPB >= 10 then 'II kategorija'
                        else 'III kategorija' end kategorija
from DA.PREDMET