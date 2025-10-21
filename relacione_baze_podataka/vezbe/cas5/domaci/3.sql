select d.INDEKS, d.IME, d.PREZIME, d.MESTORODJENJA,
       dayname((select min(i1.DATPOLAGANJA) from DA.ISPIT i1 where i1.INDEKS = d.INDEKS and i1.STATUS = 'o'))
from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS
where locate('o', lower(d.MESTORODJENJA)) > 0 and locate('a', lower(d.MESTORODJENJA)) > 0
    and locate('o', lower(d.MESTORODJENJA)) < locate('a', lower(d.MESTORODJENJA))
group by d.INDEKS, d.IME, d.PREZIME, d.MESTORODJENJA
having count(*) >= 3 and max(case when i.STATUS = 'o' and i.OCENA > 5 then OCENA else NULL end) = 9
order by d.MESTORODJENJA, d.INDEKS