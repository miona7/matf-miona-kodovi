with prosek_mesta as (
    select d.MESTORODJENJA mesto, decimal(avg(i.OCENA*1.0), 4, 2) prosek
    from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    where d.DATDIPLOMIRANJA is not null
    group by d.MESTORODJENJA
), prosek_studenta as (
    select d.INDEKS student, decimal(avg(i.OCENA*1.0), 4, 2) prosek
    from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    group by d.INDEKS
)
select d.INDEKS "indeks",
       case
           when ps.prosek >= coalesce(pm.prosek, 7.5) then d.IME || ' ' || d.PREZIME
                                            || ' ima bolji prosek od svojih sugradjana'
            else d.IME || ' ' || d.PREZIME || ' ima losiji prosek od svojih sugradjana' end "komentar",
        abs(ps.prosek - coalesce(pm.prosek, 7.5)) "Razlika proseka studenta i proseka mesta"
from DA.DOSIJE d join DA.UPISGODINE ug on d.INDEKS = ug.INDEKS
    left join prosek_mesta pm on d.MESTORODJENJA = pm.mesto
    join prosek_studenta ps on d.INDEKS = ps.student
group by d.INDEKS, d.IME, d.PREZIME, ps.prosek, pm.prosek, d.MESTORODJENJA
having abs(ps.prosek - coalesce(pm.prosek, 7.5)) <= 1.0 and count(distinct ug.SKGODINA) = 5
order by d.MESTORODJENJA desc, ps.prosek