with polozili as (
    select INDEKS
    from DA.ISPIT
    where STATUS = 'o' and OCENA > 5
    group by INDEKS
    having count(*) > 0
)
select d.IME, d.PREZIME, p.NAZIV
from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    join DA.PREDMET p on i.IDPREDMETA = p.ID
where d.INDEKS in (select INDEKS from polozili) and not exists(
    select *
    from DA.ISPIT i1
    where i1.INDEKS = d.INDEKS and i1.IDPREDMETA = p.ID and (i1.OZNAKAROKA <> i.OZNAKAROKA
      or i1.SKGODINA <> i.SKGODINA)
);


with student_predmet_polaganja as (
    select i.INDEKS student, p.NAZIV predmet, count(*) polagano,
           sum(case when i.STATUS = 'o' and i.OCENA > 5 then 1 else 0 end) polozeno
    from DA.ISPIT i join DA.PREDMET p on i.IDPREDMETA = p.ID
    group by i.INDEKS, p.NAZIV, p.ID
)
select d.IME, d.PREZIME, spp.predmet
from DA.DOSIJE d join student_predmet_polaganja spp on d.INDEKS = spp.student
where spp.polagano = 1 and spp.polozeno = 1