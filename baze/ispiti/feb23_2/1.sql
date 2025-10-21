select d1.INDEKS, d1.IME || ' ' || d1.PREZIME "Ime i prezime",
       d2.INDEKS, d2.IME || ' ' || d2.PREZIME "Ime i prezime",
       lower(substr(d1.PREZIME, 1, 3) || substr(d1.IME, 1, 1) || substr(d2.IME, 1, 1)) "Naziv para"
from DA.DOSIJE d1 join DA.DOSIJE d2 on d1.INDEKS < d2.INDEKS
where substr(d1.PREZIME, 1, 3) = substr(d2.PREZIME, 1, 3) and year(d1.DATUPISA) <> year(d2.DATUPISA)
    and exists(
        select *
        from DA.ISPIT i1
        where i1.INDEKS = d1.INDEKS and i1.STATUS = 'o' and i1.OCENA > 5
            and exists(
                select *
                from DA.ISPIT i2
                where i2.INDEKS = d2.INDEKS and i2.IDPREDMETA = i1.IDPREDMETA
                    and i2.STATUS = 'o' and i2.OCENA > 5 and i1.POENI + 10 = i2.POENI
        )
)
