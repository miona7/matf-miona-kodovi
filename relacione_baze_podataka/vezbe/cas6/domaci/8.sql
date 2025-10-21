with polozeni_espb as (
    select i.INDEKS, sum(p.ESPB) poeni
    from DA.ISPIT i join DA.PREDMET p on i.IDPREDMETA = p.ID and i.STATUS = 'o' and i.OCENA > 5
    group by i.INDEKS
)
select d.INDEKS, d.IME, d.PREZIME, pe.poeni
from DA.DOSIJE d join polozeni_espb pe on d.INDEKS = pe.INDEKS
where not exists(
    select *
    from polozeni_espb p
    where p.INDEKS <> d.INDEKS and p.poeni > pe.poeni
);

with polozeni_espb as (
    select i.INDEKS, sum(p.ESPB) poeni
    from DA.ISPIT i join DA.PREDMET p on i.IDPREDMETA = p.ID and i.STATUS = 'o' and i.OCENA > 5
    group by i.INDEKS
)
select d.INDEKS, d.IME, d.PREZIME, pe.poeni
from DA.DOSIJE d join polozeni_espb pe on d.INDEKS = pe.INDEKS
where pe.poeni = (select max(poeni) from polozeni_espb)