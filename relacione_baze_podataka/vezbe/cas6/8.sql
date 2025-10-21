with student_ocene_predmeti as (
    select i.INDEKS student, p.NAZIV predmet, p.ID id, i.OCENA ocena
    from DA.ISPIT i left join DA.PREDMET p on i.IDPREDMETA = p.ID and i.STATUS = 'o' and i.OCENA > 5
    where i.OCENA >= all (
        select i1.OCENA
        from DA.ISPIT i1
        where i1.INDEKS = i.INDEKS and i.STATUS = 'o' and i.OCENA > 5
    )
)
select d.IME, s.predmet, s.ocena,
                case
                    when s.ocena is null then 'NULL'
                    when s.ocena < 10 then repeat(substr(d.IME, 1, 1) || substr(s.predmet, 1, 1), s.ocena)
                    else repeat(substr(d.IME, length(d.IME)), 10) end dugi_kod
from DA.DOSIJE d left join student_ocene_predmeti s on d.INDEKS = s.student
order by d.IME desc;
-- ne valja


SELECT D.IME, P.NAZIV, I.OCENA,
CASE
WHEN OCENA IS NULL THEN 'NULL'
WHEN OCENA<10 THEN REPEAT( SUBSTRING(IME, 1, 1) || SUBSTRING(NAZIV, 1, 1) ,I.OCENA)
ELSE REPEAT(SUBSTRING(IME, LENGTH(IME)), 10)
END DUGI_KOD
FROM DA.DOSIJE D LEFT JOIN DA.ISPIT I
ON D.INDEKS = I.INDEKS AND OCENA>5 AND STATUS='o'
LEFT JOIN DA.PREDMET P
ON P.ID = I.IDPREDMETA
WHERE NOT EXISTS (
SELECT *
FROM DA.ISPIT I1 JOIN DA.DOSIJE D1
ON I1.INDEKS = D1.INDEKS
WHERE D1.IME = D.IME AND I1.OCENA>I.OCENA AND STATUS='o'
)
ORDER BY IME DESC;