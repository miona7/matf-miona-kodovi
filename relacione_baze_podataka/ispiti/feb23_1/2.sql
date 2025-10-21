with tmp as (
    select sp.ID, sp.NAZIV, avg(case when DATDIPLOMIRANJA is null then OCENA * 1.0 else null end) bez_diplome,
    avg(case when DATDIPLOMIRANJA is not null then OCENA * 1.0 else null end) diplomirali
    from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and STATUS = 'o' and OCENA > 5
            join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
    group by sp.ID, sp.NAZIV
)
select d.INDEKS, d.IME, d.PREZIME, avg(OCENA * 1.0) prosek,
       case when avg(OCENA * 1.0) > diplomirali then 'Prosek bolji od proseka smera'
            else 'Smer ' || t.NAZIV || ' ima bolji prosek' end "komentar za studenta"
from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and STATUS = 'o' and OCENA > 5
                join tmp t on d.IDPROGRAMA = t.ID
where DATDIPLOMIRANJA is not null
group by d.INDEKS, d.IME, d.PREZIME, t.diplomirali, t.NAZIV
having avg(OCENA * 1.0) between 7.5 and 9.0
union
select d.INDEKS, d.IME, d.PREZIME, coalesce(avg(OCENA * 1.0), -1.0) prosek,
       case when avg(OCENA * 1.0) is null then 'nema ispita'
           when avg(OCENA * 1.0) > bez_diplome then 'Odlican za sad'
            else 'moze bolje' end "komentar za studenta"
from DA.DOSIJE d join tmp t on d.IDPROGRAMA = t.ID
        left join DA.ISPIT i on d.INDEKS = i.INDEKS and STATUS = 'o' and OCENA > 5
where DATDIPLOMIRANJA is null
group by d.INDEKS, d.IME, d.PREZIME, t.bez_diplome
having count(OCENA) in (0, 2, 3, 5, 7, 9)
order by "komentar za studenta" desc;
