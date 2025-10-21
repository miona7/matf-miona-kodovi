with br_polozenih_obaveznih_predmeta as (
    select d.INDEKS indeks, sum(case when STATUS = 'o' and OCENA > 5 then 1 else 0 end) br_pol
    from DA.DOSIJE d right join DA.ISPIT i on i.INDEKS = d.INDEKS
                    right join DA.PREDMETPROGRAMA pp on i.IDPREDMETA = pp.IDPREDMETA and VRSTA = 'obavezan'
    group by d.INDEKS
)
select IME || ' ' || PREZIME "Ime prezime",
       case when POL = 'm' then 'Student je jedini koji' else 'Studentkinja je jedina koja' end
           || ' je uspisala ' || SKGODINA || ' skolsku godinu' "Komentar",
            days(current_date) - days(d.DATUPISA) "Proteklo dana"
from DA.DOSIJE d join DA.UPISGODINE ug on d.INDEKS = ug.INDEKS
                    join br_polozenih_obaveznih_predmeta bop on d.INDEKS = bop.indeks
where not exists(
    select *
    from DA.DOSIJE d1 join DA.UPISGODINE ug1 on d1.INDEKS = ug1.INDEKS
    where d1.MESTORODJENJA = d.MESTORODJENJA and ug1.SKGODINA = ug.SKGODINA and d1.INDEKS <> d.INDEKS
)
order by "Proteklo dana" desc;

select *
from DA.DOSIJE d
where year(DATUPISA) = 2024
;

insert into DA.DOSIJE(INDEKS, IDPROGRAMA, IME, PREZIME, POL, MESTORODJENJA, IDSTATUSA, DATUPISA)
values (2022133, 101, 'Miona', 'Sretenovic', 'z', 'Krusevac', 1, current_date )

insert into DA.SKOLSKAGODINA
values (2024, date('01.10.2024'), date('31.5.2025'));


insert into DA.UPISGODINE(INDEKS, SKGODINA, IDSTATUSA, DATUPISA)
values (2022133, 2024,1, current_date)