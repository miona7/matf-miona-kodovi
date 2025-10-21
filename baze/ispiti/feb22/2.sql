with prijavili_bar_3_ispita as (
    select i.INDEKS indeks
    from DA.ISPIT i
    group by i.INDEKS
    having sum(case when i.IDPREDMETA is not null then 1 else 0 end) >= 3
), najveci_broj_poena_po_smeru as (
    select sp.ID smer, MAX(i.POENI) poeni
    from DA.ISPIT i join DA.DOSIJE d on i.INDEKS = d.INDEKS
        join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
    where i.STATUS = 'o' and i.OCENA > 5
    group by sp.ID
    having MAX(i.POENI)
)
select distinct d.INDEKS, d.IME, d.PREZIME, sum(case when i.IDPREDMETA is not null then 1 else 0 end) br_prijavljenih,
                sum(case when i.STATUS = 'o' and i.OCENA > 5 then 1 else 0 end) br_polozenih,
                decimal(avg(case when i.STATUS = 'o' and i.OCENA > 5 then OCENA * 1.0 else null end), 4, 2) prosek
from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS
where exists(
    select *
    from DA.ISPIT i2
    where i2.INDEKS = d.INDEKS and i2.STATUS = 'o' and i2.OCENA > 5
        and i2.POENI = (
            select poeni
            from najveci_broj_poena_po_smeru
            where d.IDPROGRAMA = smer)
) and d.INDEKS in (select indeks from prijavili_bar_3_ispita)
group by d.INDEKS, d.IME, d.PREZIME
order by prosek, d.INDEKS desc;
