create function cena_predmeta(f_idpredmeta integer)
returns integer
return
    (select ESPB
    from DA.PREDMET
    where ID = f_idpredmeta) * 2000;

select NAZIV, ESPB, DA.cena_predmeta(ID)
from DA.PREDMET;