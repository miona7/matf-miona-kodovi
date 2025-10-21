select p.NAZIV, d.IME, d.PREZIME
from DA.PREDMET p join DA.ISPIT i on p.ID = i.IDPREDMETA join DA.DOSIJE d on d.INDEKS = i.INDEKS
where i.DATPOLAGANJA is not null and i.DATPOLAGANJA <= all (
    select i2.DATPOLAGANJA
    from DA.ISPIT i2
    where i2.DATPOLAGANJA is not null
) and exists(
    select *
    from DA.UPISANKURS uk
    where uk.INDEKS = d.INDEKS and p.ID = uk.IDPREDMETA
);

select p.NAZIV
from DA.PREDMET p join DA.ISPIT i on p.ID = i.IDPREDMETA
where i.DATPOLAGANJA is not null and i.DATPOLAGANJA <= all (
    select i2.DATPOLAGANJA
    from DA.ISPIT i2
    where i2.DATPOLAGANJA is not null
)
