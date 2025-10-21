create function cena_predmeta(f_espb smallint)
returns integer
return f_espb * 2000;

drop function cena_predmeta;

select NAZIV, ESPB, DA.cena_predmeta(ESPB)
from DA.PREDMET;