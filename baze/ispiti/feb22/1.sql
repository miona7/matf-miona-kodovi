with tmp as (
    select distinct i.INDEKS indeks
    from DA.ISPIT i
    where i.STATUS = 'o' and i.OCENA > 5 and exists(
        select *
        from DA.PREDMET p
        where p.ESPB = 6 and i.IDPREDMETA = p.ID
    )
    order by indeks
)
select d.INDEKS, d.IME, d.PREZIME, substr(d.MESTORODJENJA, 1, 2), year(d.DATUPISA), monthname(d.DATUPISA),
    coalesce(pi.NAZIVPREDMETA, 'nema priznat predmet') "Priznati predmet"
from DA.DOSIJE d left join tmp t on d.INDEKS = t.indeks
                left join DA.PRIZNATISPIT pi on d.INDEKS = pi.INDEKS
order by d.INDEKS;



select *
from DA.ISPIT;