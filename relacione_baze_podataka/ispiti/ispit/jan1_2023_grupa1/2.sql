with prosek_mesta as (
    select d.MESTORODJENJA mesto, coalesce(decimal(avg(i.OCENA * 1.0), 4, 2), 5.0) prosek
    from DA.DOSIJE d left join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    where d.DATDIPLOMIRANJA is not null
    group by d.MESTORODJENJA
)
select d.INDEKS "indeks",
       d.IME || ' ' || d.PREZIME || ' ima bolji prosek od proseka mesta ' || d.MESTORODJENJA "komentar",
       decimal(avg(i.OCENA * 1.0), 4, 2) - pm.prosek "Razlika proseka studenta i proseka mesta"
from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    join DA.UPISGODINE ug on d.INDEKS = ug.INDEKS
    join prosek_mesta pm on d.MESTORODJENJA = pm.mesto
where d.DATDIPLOMIRANJA is null
group by d.INDEKS, d.IME, d.PREZIME, d.MESTORODJENJA, pm.prosek
having decimal(avg(i.OCENA * 1.0), 4, 2) > pm.prosek and count(distinct ug.SKGODINA) > 4
order by d.MESTORODJENJA, 3 desc