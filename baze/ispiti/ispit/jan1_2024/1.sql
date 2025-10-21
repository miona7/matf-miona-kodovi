select d.INDEKS "indeks", d.IME "ime", d.PREZIME "prezime", d.MESTORODJENJA "mestorodjenja",
        decimal(avg(case when i.OCENA > 5 and i.STATUS = 'o' then i.OCENA * 1.0 else null end), 4, 2) "prosek",
        d.IME || ' ' || d.PREZIME || ' (' || replace(d.MESTORODJENJA, 'Beograd', 'Bg') || ')' "Kod"
from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS
    join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
where sp.NAZIV = 'Informatika'
group by d.INDEKS, d.IME, d.PREZIME, d.MESTORODJENJA
having 2 > sum(case when i.STATUS = 'x' then 1 else 0 end)