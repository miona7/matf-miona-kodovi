create table student_podaci(
    indeks integer,
    broj_predmeta smallint,
    prosek float,
    datupisa date
);

insert into student_podaci(indeks, broj_predmeta, prosek)
select d.INDEKS, count(i.IDPREDMETA), avg(i.OCENA * 1.0)
from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i .INDEKS and i.STATUS = 'o' and i.OCENA > 5
    and d.DATDIPLOMIRANJA is null
group by d.INDEKS
having avg(i.OCENA * 1.0) > 8.0
union
select d.INDEKS, 10, 10
from DA.DOSIJE d
where d.DATDIPLOMIRANJA is not null;

merge into student_podaci sp
using (
    select d.INDEKS, count(i.IDPREDMETA) br_p, avg(i.OCENA * 1.0) p, ss.NAZIV status, d.DATUPISA upis
    from DA.DOSIJE d left join DA.ISPIT i on i.INDEKS = d.INDEKS and i.STATUS = 'o' and i.OCENA > 5
        join DA.STUDENTSKISTATUS ss on d.IDSTATUSA = ss.ID
    group by d.INDEKS, ss.NAZIV, d.DATUPISA
) as t on sp.indeks = t.INDEKS
when matched and t.status = 'Diplomirao' then
    update
        set datupisa = t.upis
when matched and t.status = 'Budzet' then
    update
        set (broj_predmeta, prosek) = (t.br_p, t.p)
when matched and t.status like 'Ispis%' then
    delete
when not matched and t.status not like 'Ispis%' then
    insert (indeks, broj_predmeta, prosek)
    values (t.INDEKS, t.br_p, t.p);

drop table student_podaci;