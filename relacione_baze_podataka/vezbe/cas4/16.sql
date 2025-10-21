select i.INDEKS, p.NAZIV, i.OCENA, substr((current_date - i.DATPOLAGANJA), 1, 1) godine,
       substr((current_date - i.DATPOLAGANJA), 2, 2) meseci, substr((current_date - i.DATPOLAGANJA), 4) dani
from DA.ISPIT i join DA.PREDMET p on i.IDPREDMETA = p.ID
where DATPOLAGANJA >= current_date - 5 years;

select i.INDEKS, p.NAZIV, i.OCENA,
       year(current_date - i.DATPOLAGANJA) godine,
       month(current_date - i.DATPOLAGANJA) meseci,
       day(current_date - i.DATPOLAGANJA) dani
from DA.ISPIT i join DA.PREDMET p on i.IDPREDMETA = p.ID
where DATPOLAGANJA >= current_date - 5 years;