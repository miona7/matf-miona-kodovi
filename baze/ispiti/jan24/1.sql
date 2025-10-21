with prosek as (
    select d.INDEKS, decimal(avg(OCENA * 1.0), 4, 2) prosek
    from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and STATUS = 'o' and OCENA > 5
    group by d.INDEKS
)
select d.INDEKS, IME, PREZIME, MESTORODJENJA, prosek,
       IME || ' ' || PREZIME || ' (' ||
            case
                when MESTORODJENJA like 'Beograd%' then replace(MESTORODJENJA, 'Beograd', 'Bg')
                else MESTORODJENJA end || ')' "Kod"
from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID and NAZIV = 'Informatika'
                join DA.ISPIT i on d.INDEKS = i.INDEKS join prosek p on p.INDEKS = d.INDEKS
group by d.INDEKS, IME, PREZIME, MESTORODJENJA, prosek, NAZIV
having sum(case when STATUS = 'x' and OCENA > 5 then 1 else 0 end) < 2