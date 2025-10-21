with diplomirani as(
    select d.INDEKS
    from DA.DOSIJE d
    where d.DATDIPLOMIRANJA is not null
), isto_polozeno as(
    select i1.INDEKS indeks1, i2.INDEKS indeks2,
        sum(case when i1.OCENA > 5 and i2.OCENA > 5 and i1.OCENA = i2.OCENA then 1 else 0 end) ista_ocena
    from DA.ISPIT i1 join DA.ISPIT i2 on i1.IDPREDMETA = i2.IDPREDMETA
        and i1.STATUS not in ('p', 'n') and i2.STATUS not in ('p', 'n')
            and i1.INDEKS < i2.INDEKS
                and i1.INDEKS in (select d.INDEKS from diplomirani d)
                and i2.INDEKS in (select d.INDEKS from diplomirani d)
    group by i1.INDEKS, i2.INDEKS
    having count(*) >= 5
), tri_ista_ocena as (
    select i1.INDEKS indeks1, i2.INDEKS indeks2, count(*) br_predmeta
    from DA.ISPIT i1 join DA.ISPIT i2 on i1.IDPREDMETA = i2.IDPREDMETA
        and i1.STATUS = 'o' and i2.STATUS = 'o' and i1.OCENA > 5 and i2.OCENA > 5
            and i1.OCENA = i2.OCENA and i1.INDEKS < i2.INDEKS
                and i1.INDEKS in (select d.INDEKS from diplomirani d)
                and i2.INDEKS in (select d.INDEKS from diplomirani d)
    where exists(
        select *
        from DA.DOSIJE d1 join DA.DOSIJE d3 on d1.IME = d3.IME
            join DA.ISPIT i3 on i3.INDEKS = d3.INDEKS
        where d1.INDEKS = i1.INDEKS and i3.IDPREDMETA = i1.IDPREDMETA
            and i3.STATUS = 'o' and i3.OCENA > 5 and i1.OCENA = i3.OCENA
                and i3.INDEKS <> i1.INDEKS and i3.INDEKS <> i2.INDEKS
    )
    group by i1.INDEKS, i2.INDEKS
)
select d1.IME || ' ' || d1.PREZIME || ', ' || d2.IME || ' ' || d2.PREZIME "ime i prezime",
       ip.ista_ocena "Broj predmeta sa istom ocenom", tio.br_predmeta "Broj predmeta sa istom ocenom i trecim imenjakom"
from isto_polozeno ip join tri_ista_ocena tio on ip.indeks1 = tio.indeks1 and ip.indeks2 = tio.indeks2
    join DA.DOSIJE d1 on d1.INDEKS = ip.indeks1 join DA.DOSIJE d2 on d2.INDEKS = ip.indeks2
where d1.IME = d2.IME