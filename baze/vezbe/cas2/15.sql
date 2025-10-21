select d.INDEKS, d.IME, d.PREZIME, p.NAZIV, i.OCENA
from DA.DOSIJE d left join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    left join DA.PREDMET p on i.IDPREDMETA = p.ID
where d.IME like '%ark%'
order by d.INDEKS