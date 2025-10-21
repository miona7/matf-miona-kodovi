select sp.NAZIV || ' ' || d.IME || ' ' || d.PREZIME "niska", d.INDEKS "indeks", d.DATUPISA "datum",
       coalesce(p.NAZIV, 'Nema polozenih kurseva') "predmet", coalesce(i.OCENA, -1) "ocena"
from DA.DOSIJE d left join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    left join DA.PREDMET p on i.IDPREDMETA = p.ID
    join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
where d.MESTORODJENJA like '_a%' and not exists(
    select *
    from DA.DOSIJE d1
    where d1.IDPROGRAMA = d.IDPROGRAMA and d1.IME = d.IME and d1.INDEKS <> d.INDEKS
)