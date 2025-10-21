with prosek_mesta as (
    select MESTORODJENJA mesto, coalesce(avg(OCENA * 1.0), 7.5) prosek
    from DA.DOSIJE d left join DA.ISPIT i on d.INDEKS = i.INDEKS and STATUS = 'o' and OCENA > 5
    where DATDIPLOMIRANJA is not null
    group by MESTORODJENJA
)
select d.INDEKS, IME || ' ' || PREZIME || ' ima ' ||
                case when avg(OCENA * 1.0) > prosek then 'bolji' else 'losiji' end
                     || ' prosek od svojih sugradjanja' komentar, MESTORODJENJA, abs(avg(OCENA * 1.0) - prosek) razlika
from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and STATUS = 'o' and OCENA > 5
                join prosek_mesta pm on d.MESTORODJENJA = pm.mesto
where DATDIPLOMIRANJA is not null and 5 = (select count(*) from DA.UPISGODINE ug where ug.INDEKS = d.INDEKS)
group by d.INDEKS, IME, PREZIME, prosek, MESTORODJENJA
having abs(avg(OCENA * 1.0) - prosek) <= 0.1
order by MESTORODJENJA desc, 4