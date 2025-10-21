with polozeni_espb as (
    select i.INDEKS student, sum(p.ESPB) bodovi
    from DA.ISPIT i join DA.PREDMET p on i.IDPREDMETA = p.ID and i.STATUS = 'o' and i.OCENA > 5
    group by i.INDEKS
), st_sa_max_espb_na_smeru as (
    select sp.ID idprograma, sp.NAZIV program, max(bodovi) poeni
    from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
        join polozeni_espb p on d.INDEKS = p.student
    group by sp.ID, sp.NAZIV
)
select program, d.INDEKS, d.IME, d.PREZIME, s.poeni
from st_sa_max_espb_na_smeru s join DA.DOSIJE d on s.idprograma = d.IDPROGRAMA
where s.poeni = (select bodovi from polozeni_espb where d.INDEKS = polozeni_espb.student)
order by s.idprograma