with prosek_mesta as (
    select d.MESTORODJENJA mesto, coalesce(decimal(avg(i.OCENA*1.0), 4, 2), 7.5) prosek
    from DA.DOSIJE d left join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
        and d.DATDIPLOMIRANJA is not null
    group by d.MESTORODJENJA
)
select d.INDEKS "indeks",
       case
           when decimal(avg(i.OCENA)*1.0, 4, 2) >= pm.prosek then d.IME || ' ' || d.PREZIME
                                            || ' ima bolji prosek od svojih sugradjana'
            else d.IME || ' ' || d.PREZIME || ' ima losiji prosek od svojih sugradjana' end "komentar",
        abs(decimal(avg(i.OCENA)*1.0, 4, 2) - pm.prosek) "Razlika proseka studenta i proseka mesta"
from DA.DOSIJE d join prosek_mesta pm on d.MESTORODJENJA = pm.mesto
    join DA.ISPIT i on d.INDEKS = i.INDEKS and i.OCENA > 5 and i.STATUS = 'o'
where d.DATDIPLOMIRANJA is not null
    and 5 = (select count(distinct ug.SKGODINA) from DA.UPISGODINE ug where d.INDEKS = ug.INDEKS)
group by d.INDEKS, d.IME, d.PREZIME, pm.prosek, d.MESTORODJENJA
having abs(decimal(avg(i.OCENA)*1.0, 4, 2) - pm.prosek) <= 1.0
order by d.MESTORODJENJA desc, 3