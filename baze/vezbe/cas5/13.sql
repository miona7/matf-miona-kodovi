select p.NAZIV, coalesce(d.IME || ' ' || d.PREZIME, 'nema')
from DA.PREDMET p left join DA.ISPIT i on p.ID = i.IDPREDMETA and i.STATUS = 'o' and i.OCENA > 5
    left join DA.DOSIJE d on i.INDEKS = d.INDEKS
where p.ESPB = (select min(p1.ESPB) from DA.PREDMET p1)