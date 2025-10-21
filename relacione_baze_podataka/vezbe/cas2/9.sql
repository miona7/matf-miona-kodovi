select distinct d.INDEKS, d.IME, d.PREZIME
from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    join DA.PREDMET p on i.IDPREDMETA = p.ID
where d.PREZIME like '___a%c' and p.ESPB between 2 and 10 and i.OCENA in (6, 8, 10)
    and i.DATPOLAGANJA between '5.1.2018' and '15.12.2018'
order by d.PREZIME, d.IME desc