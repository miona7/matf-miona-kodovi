select distinct case
        when POL = 'm' then 'student' || ' ' || PREZIME || ' ' || IME
        when POL = 'z' then 'studentkinja' || ' ' || PREZIME || ' ' || IME
        end, d.INDEKS, MESTORODJENJA, sp.NAZIV, p.NAZIV, i.OCENA
from DA.DOSIJE d join DA.ISPIT i on i.INDEKS = d.INDEKS and STATUS = 'o' and OCENA > 5
                join DA.PREDMET p on i.IDPREDMETA = p.ID
                join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
where MESTORODJENJA like 'Beograd%'
union
select distinct case
        when POL = 'm' then 'student' || ' ' || PREZIME || ' ' || IME
        when POL = 'z' then 'studentkinja' || ' ' || PREZIME || ' ' || IME
        end, d.INDEKS, MESTORODJENJA, sp.NAZIV, 'Nema polozenih ispita', null
from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
where MESTORODJENJA like 'Beograd%'
    and not exists(
        select *
        from DA.ISPIT i
        where i.INDEKS = d.INDEKS and STATUS = 'o' and OCENA > 5
)
