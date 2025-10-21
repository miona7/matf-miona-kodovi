with tmp as (
    select max(substr(d.INDEKS, 5)) indeks
    from DA.DOSIJE d
)
select sp.NAZIV || ' ' || PREZIME || ' ' || IME, d.INDEKS, MESTORODJENJA, p.NAZIV, OCENA
from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
                join DA.ISPIT i on d.INDEKS = i.INDEKS and STATUS = 'o' and OCENA > 5
                join DA.PREDMET p on p.ID = i.IDPREDMETA
where MESTORODJENJA like 'K%' and substr(d.INDEKS, 5) = (select indeks from tmp)
union
select sp.NAZIV || ' ' || PREZIME || ' ' || IME, d.INDEKS, MESTORODJENJA, 'Nema polozenih predmeta', null
from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
where MESTORODJENJA like 'K%' and substr(d.INDEKS, 5) = (select indeks from tmp)
        and not exists(select * from DA.ISPIT i where d.INDEKS = i.INDEKS and STATUS = 'o' and OCENA > 5)