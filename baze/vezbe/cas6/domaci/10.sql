with tmp as (
    select i.INDEKS, sum(p.ESPB) polozeno
    from DA.ISPIT i join DA.PREDMET p on i.IDPREDMETA = p.ID and i.STATUS = 'o' and i.OCENA > 5
    group by i.INDEKS
), tmp1 as (
    select d.INDEKS
    from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
        join tmp on d.INDEKS = tmp.INDEKS
    where polozeno * 2 >= sp.OBIMESPB
)
select nk.NAZIV, sp.ZVANJE, sp.NAZIV, sp.OBIMESPB, count(d.INDEKS) br_studenata,
    sum(case when d.DATDIPLOMIRANJA is not null then 1 else 0 end ) * 1.0 / count(d.INDEKS) * 1.0 procenat_diplomiranih,
    sum(case when ss.ID = -1 then 1 else 0 end ) * 1.0 / count(d.INDEKS) * 1.0 procenat_ispisanih,
    sum(case when d.INDEKS in (select INDEKS from tmp1) then 1 else 0 end) *  1.0 / count(d.INDEKS) * 1.0 procenat_pola
from DA.NIVOKVALIFIKACIJE nk join DA.STUDIJSKIPROGRAM sp on nk.ID = sp.IDNIVOA
    join DA.DOSIJE d on d.IDPROGRAMA = sp.ID
    join DA.STUDENTSKISTATUS ss on d.IDSTATUSA = ss.ID
group by nk.NAZIV, sp.ZVANJE, sp.NAZIV, sp.OBIMESPB, sp.ID;

select d.INDEKS, d.IME, d.PREZIME, sum(p.ESPB)
from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    join DA.PREDMET p on i.IDPREDMETA = p.ID
    join DA.STUDIJSKIPROGRAM ss on d.IDPROGRAMA = ss.ID
    join DA.NIVOKVALIFIKACIJE nk on ss.IDNIVOA = nk.ID
where d.IDPROGRAMA = 303 and nk.ID = 3
group by d.INDEKS, d.IME, d.PREZIME