with manje_od_5 as (
    select d.INDEKS student
    from DA.DOSIJE d left join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
        left join DA.PREDMETPROGRAMA pp on d.IDPROGRAMA = pp.IDPROGRAMA and i.IDPREDMETA = pp.IDPREDMETA
    where pp.VRSTA = 'obavezan'
    group by d.INDEKS
    having count(distinct i.IDPREDMETA) < 5
)
select d.IME || ' ' || d.PREZIME "Ime i prezime",
       case
            when d.POL = 'z' then 'Studentkinja je jedina iz mesta ' || d.MESTORODJENJA ||
                                    ' koja je upisala ' || ug.SKGODINA || ' skolsku godinu'
            else 'Student je jedini iz mesta ' || d.MESTORODJENJA ||
                                    ' koja je upisala ' || ug.SKGODINA || ' skolsku godinu' end "Komentar",
    days_between(current_date, d.DATUPISA) "Proteklo dana"
from DA.DOSIJE d join DA.UPISGODINE ug on d.INDEKS = ug.INDEKS
where not exists(
    select *
    from DA.DOSIJE d1 join DA.UPISGODINE ug1 on d1.INDEKS = ug1.INDEKS
    where d1.INDEKS <> d.INDEKS and ug1.SKGODINA = ug.SKGODINA and d.MESTORODJENJA = d1.MESTORODJENJA
) and d.INDEKS in (select student from manje_od_5)
order by "Proteklo dana" desc