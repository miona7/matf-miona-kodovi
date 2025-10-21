select *
from DA.PREDMET p
where p.ESPB >= all (
    select ESPB
    from DA.PREDMET
)