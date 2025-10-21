with tmp as (
    select i.INDEKS indeks, i.SKGODINA godina
    from DA.ISPIT i join DA.PREDMET p on i.IDPREDMETA = p.ID
    where i.STATUS = 'o' and i.OCENA > 5
    group by i.INDEKS, i.SKGODINA
    having count(*) > 5 and sum(p.ESPB) > 30
)
select d.IME || ' ' || d.PREZIME student, i.POENI poeni, p.NAZIV predmet, i.SKGODINA godina,
       case
           when i.POENI <= 50 then 'Student je pao'
            when i.POENI in (60, 70, 80, 90) then 'Student zeli visu ocenu'
             else 'Student ne zeli nista da ponisti' end komentar
from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and i.STATUS = 'o'
                    join DA.PREDMET p on i.IDPREDMETA = p.ID
where i.SKGODINA in (select godina from tmp where d.INDEKS = indeks)
order by d.INDEKS, godina desc