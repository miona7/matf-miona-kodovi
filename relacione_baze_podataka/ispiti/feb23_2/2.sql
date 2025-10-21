with tmp as (
    select sp.ID smer, sp.NAZIV, avg(case when DATDIPLOMIRANJA is not null then OCENA * 1.0 else null end) diplomirali,
           avg(case when DATDIPLOMIRANJA is null then OCENA * 1.0 else null end) bez_diplome
    from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
                join DA.ISPIT i on i.INDEKS = d.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    group by sp.ID, sp.NAZIV
)
select d.INDEKS, d.IME, d.PREZIME, avg(OCENA*1.0) prosek,
       case when avg(OCENA*1.0) < t.diplomirali then 'Prosek je losiji od proseka smera ' || t.NAZIV
           else 'Student ima bolji prosek' end "komentar za studenta"
from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    join tmp t on t.smer = d.IDPROGRAMA
where d.DATDIPLOMIRANJA is not null
group by d.INDEKS, d.IME, d.PREZIME, t.diplomirali, t.NAZIV
having avg(OCENA*1.0) not between 7.5 and 9.0
union
select d.INDEKS, d.IME, d.PREZIME, coalesce(avg(OCENA*1.0), 5.0) prosek,
       case when avg(OCENA*1.0) is null then 'Nema ispita'
            when avg(OCENA*1.0) > t.bez_diplome then 'Odlican za sad'
            else 'Moze bolje' end "komentar za studenta"
from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    join tmp t on t.smer = d.IDPROGRAMA
where d.DATDIPLOMIRANJA is null
group by d.INDEKS, d.IME, d.PREZIME, t.bez_diplome
having count(i.IDPREDMETA) < 10
order by "komentar za studenta" desc