select *
from DA.DOSIJE
where DATDIPLOMIRANJA is not null and DATDIPLOMIRANJA <= all (
    select DATDIPLOMIRANJA
    from DA.DOSIJE
    where DATDIPLOMIRANJA is not null
)