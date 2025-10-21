select d1.INDEKS, d1.IME, d1.PREZIME, d2.INDEKS, d2.IME, d2.PREZIME
from DA.DOSIJE d1 join DA.DOSIJE d2 on d1.INDEKS < d2.INDEKS and d1.IME like 'M%' and d2.IME like 'M%'
    join DA.ISPIT i1 on d1.INDEKS = i1.INDEKS and i1.STATUS = 'o' and i1.OCENA > 5
    join DA.ISPIT i2 on d2.INDEKS = i2.INDEKS and i2.STATUS = 'o' and i2.OCENA > 5
    and i1.IDPREDMETA = i2.IDPREDMETA and i1.OZNAKAROKA = i2.OZNAKAROKA and i1.SKGODINA = i2.SKGODINA
group by d1.INDEKS, d1.IME, d1.PREZIME, d2.INDEKS, d2.IME, d2.PREZIME
having count(*) >= 2