select *
from DA.PREDMET p
where exists(
    select *
    from DA.UPISANKURS uk
    where uk.IDPREDMETA = p.ID
)