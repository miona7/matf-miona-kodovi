with tmp as (
    select i.INDEKS, sum(case when i.STATUS = 'o' and i.OCENA > 5 and p.ESPB = 6 then 1 else 0 end) br_pol
    from DA.ISPIT i join DA.PREDMET p on i.IDPREDMETA = p.ID
    group by i.INDEKS
    having sum(case when i.STATUS = 'o' and i.OCENA > 5 and p.ESPB = 6 then 1 else 0 end) > 10
            and sum(case when i.STATUS = 'o' and i.OCENA > 5 and p.ESPB > 20 then 1 else 0 end) = 0
), najtezi as (
    select p.ID predmet
    from DA.PREDMET p
    group by p.ID, p.ESPB
    having p.ESPB = (select max(p1.ESPB) from DA.PREDMET p1)
)
select d.INDEKS, d.IME || ' ' || d.PREZIME "ime i prezime", 'Polozeno ' || t.br_pol || ' predmeta od 6 espb' komentar
from DA.DOSIJE d join tmp t on d.INDEKS = t.INDEKS
union
select d.INDEKS, d.IME || ' ' || d.PREZIME, 'Polozen najtezi predmet'
from DA.DOSIJE d
where exists(
    select *
    from DA.ISPIT i
    where i.INDEKS = d.INDEKS and i.IDPREDMETA in (select predmet from najtezi)
)
order by INDEKS desc