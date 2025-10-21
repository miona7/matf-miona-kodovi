select sp.NAZIV || ' ' || d.PREZIME || ' ' || d.IME, d.INDEKS, p.NAZIV, i.OCENA
from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
    join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    join DA.PREDMET p on i.IDPREDMETA = p.ID and p.NAZIV like 'P%'
where d.MESTORODJENJA like '_a%'
    and not exists(
        select *
        from DA.DOSIJE d1
        where d1.INDEKS <> d.INDEKS and d1.IDPROGRAMA = d.IDPROGRAMA and d1.IME = d.IME
)
union all
select sp.NAZIV || ' ' || d.PREZIME || ' ' || d.IME, d.INDEKS,
       'Nema polozenih kurseva', -1
from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
where d.MESTORODJENJA like '_a%' and not exists(
        select *
        from DA.DOSIJE d1
        where d1.INDEKS <> d.INDEKS and d1.IDPROGRAMA = d.IDPROGRAMA and d1.IME = d.IME
) and not exists(
    select *
    from DA.ISPIT i join DA.PREDMET p on i.IDPREDMETA = p.ID
    where i.INDEKS = d.INDEKS and i.STATUS = 'o' and i.OCENA > 5 and p.NAZIV like 'P'
)