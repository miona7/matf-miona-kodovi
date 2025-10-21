with diplomirani as (
    select INDEKS indeks
    from DA.DOSIJE
    where DATDIPLOMIRANJA is not null
), isti_studenti_polozeno as (
    select i1.INDEKS indeks1, i2.INDEKS indeks2, count(*) polozeno_istih,
           sum (case when i1.OCENA = i2.OCENA and i1.STATUS = 'o' and i2.STATUS = 'o' then 1 else 0 end) br_predmeta_sa_istom_ocenom
    from DA.ISPIT i1 join DA.ISPIT i2 on i1.IDPREDMETA = i2.IDPREDMETA and i1.INDEKS < i2.INDEKS
        and i1.STATUS not in ('p', 'n') and i2.STATUS not in ('p', 'n')
        and i1.INDEKS in (select indeks from diplomirani) and i2.INDEKS in (select indeks from diplomirani)
    group by i1.INDEKS, i2.INDEKS
    having count(*) >= 5
), postoji_treci_student as (
    select i1.INDEKS indeks1, i2.INDEKS indeks2, count(*) polozeno_istih
    from DA.ISPIT i1 join DA.ISPIT i2 on i1.IDPREDMETA = i2.IDPREDMETA and i1.INDEKS < i2.INDEKS
        and i1.STATUS = 'o' and i1.OCENA > 5 and i1.OCENA = i2.OCENA
        and i1.INDEKS in (select indeks from diplomirani) and i2.INDEKS in (select indeks from diplomirani)
    where exists(
        select *
        from DA.ISPIT i join DA.DOSIJE d on i.INDEKS = d.INDEKS
                        join DA.DOSIJE d1 on d1.INDEKS = i1.INDEKS and d1.IME = d.IME
        where i.IDPREDMETA = i1.IDPREDMETA and i.STATUS = 'o' and i.OCENA > 5
            and i.INDEKS <> i1.INDEKS and i.INDEKS <> i2.INDEKS
    )
    group by i1.INDEKS, i2.INDEKS
)
select d1.IME || ' ' || d1.PREZIME "Ime i prezime", d2.IME || ' ' || d2.PREZIME "Ime i prezime",
       isp.polozeno_istih "Broj predmeta sa istom ocenom", pts.polozeno_istih "Broj predmeta sa istom ocenom i trecim imenjakom"
from isti_studenti_polozeno isp join postoji_treci_student pts on isp.indeks1 = pts.indeks1 and isp.indeks2 = pts.indeks2
    join DA.DOSIJE d1 on d1.INDEKS = isp.indeks1 join DA.DOSIJE d2 on d2.INDEKS = isp.indeks2
where d1.IME = d2.IME