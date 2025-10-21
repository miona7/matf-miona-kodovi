with prosek_mesta as (
    select MESTORODJENJA mesto, coalesce(avg(OCENA * 1.0), 5.0) prosek
    from DA.DOSIJE d left join DA.ISPIT i on d.INDEKS = i.INDEKS and STATUS = 'o' and OCENA > 5 and DATDIPLOMIRANJA is not null
    group by MESTORODJENJA
)
select d.INDEKS, IME || ' ' || PREZIME || ' ima bolji prosek od proseka mesta' komentar, avg(OCENA * 1.0) - pm.prosek razlika
from DA.DOSIJE d join prosek_mesta pm on d.MESTORODJENJA = pm.mesto
                join DA.ISPIT i on i.INDEKS = d.INDEKS and STATUS = 'o' and OCENA > 5
where 4 < (select count(distinct SKGODINA) from DA.UPISGODINE ug where ug.INDEKS = d.INDEKS)
        and DATDIPLOMIRANJA is null
group by d.INDEKS, IME, PREZIME, pm.prosek, MESTORODJENJA
having avg(OCENA * 1.0) > prosek
order by MESTORODJENJA, 4 desc