select *
from DA.DOSIJE
where not DATDIPLOMIRANJA <= all (
    select DATDIPLOMIRANJA
    from DA.DOSIJE
    where DATDIPLOMIRANJA is not null
) or DATDIPLOMIRANJA is null