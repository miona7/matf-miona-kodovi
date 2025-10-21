select distinct d.INDEKS, d.IME || ' ' || d.PREZIME "Prezime i ime", coalesce(p.NAZIV, '---'), coalesce(i.OCENA, -1)
from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS
    left join DA.PREDMET p on i.IDPREDMETA = p.ID and p.NAZIV like 'P%'
where length(d.IME) = length(d.PREZIME) and (month(d.DATUPISA) = 7 or month(d.DATUPISA) = 9)
and i.STATUS not in ('p', 'n');
