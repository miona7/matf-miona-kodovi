select case
        when d.POL = 'z' then 'studentkinja ' || d.PREZIME || ' ' || d.IME
        else 'student ' || d.PREZIME || ' ' || d.IME end "komentar", d.INDEKS "indeks",
        d.DATUPISA "datum", sp.NAZIV "program", coalesce(p.NAZIV, 'Nema polozenih predmeta') "predmet",
        i.OCENA "ocena"
from DA.STUDIJSKIPROGRAM sp left join DA.DOSIJE d on d.IDPROGRAMA = sp.ID
    left join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    left join DA.PREDMET p on p.ID = i.IDPREDMETA
where d.MESTORODJENJA like 'Beograd%' and d.DATUPISA = (
    select min(d1.DATUPISA)
    from DA.DOSIJE d1
    where d1.IDPROGRAMA = d.IDPROGRAMA and d1.MESTORODJENJA like 'Beograd%'
)