select *
from DA.DOSIJE
where DATDIPLOMIRANJA in (
    select DATPOLAGANJA
    from DA.ISPIT
);

select distinct *
from DA.DOSIJE d join DA.ISPIT i on d.DATDIPLOMIRANJA = i.DATPOLAGANJA