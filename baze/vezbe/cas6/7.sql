with ir_sa_min_usp as (
    select i.OZNAKAROKA, i.SKGODINA, i.INDEKS,
           decimal(sum(case when i.STATUS = 'o' and i.OCENA > 5 then 1 else 0 end) * 1.0 / count(*), 4, 2) uspesnost
    from DA.ISPIT i
    group by i.OZNAKAROKA, i.SKGODINA, i.INDEKS
    having decimal(sum(case when i.STATUS = 'o' and i.OCENA > 5 then 1 else 0 end) * 1.0 / count(*), 4, 2) <= all (
        select decimal(sum(case when i1.STATUS = 'o' and i1.OCENA > 5 then 1 else 0 end) * 1.0 / count(*), 4, 2)
        from DA.ISPIT i1
        where i.INDEKS = i1.INDEKS
        group by i1.OZNAKAROKA, i1.SKGODINA, i1.INDEKS
    )
)
select d.IME, d.PREZIME, ir.NAZIV, irmin.uspesnost
from DA.DOSIJE d join ir_sa_min_usp irmin on d.INDEKS = irmin.INDEKS
    join DA.ISPITNIROK ir on ir.OZNAKAROKA = irmin.OZNAKAROKA and ir.SKGODINA = irmin.SKGODINA
where d.MESTORODJENJA = 'Arandjelovac' and irmin.uspesnost <= all (
    select us.uspesnost
    from ir_sa_min_usp us
    where us.OZNAKAROKA = ir.OZNAKAROKA and us.SKGODINA = ir.SKGODINA
)
order by d.IME, d.PREZIME;

WITH TMP AS (
SELECT INDEKS, OZNAKAROKA, SKGODINA ,
DECIMAL(COUNT(CASE WHEN OCENA>5 AND STATUS='o' THEN 1 ELSE NULL END) * 1.0/COUNT(*), 5, 2) PROLAZNOST
FROM DA.ISPIT
GROUP BY SKGODINA, OZNAKAROKA, INDEKS
)
SELECT IME, PREZIME, NAZIV, P.PROLAZNOST
FROM TMP P JOIN DA.DOSIJE D
ON P.INDEKS = D.INDEKS
JOIN DA.ISPITNIROK IR
ON IR.SKGODINA = P.SKGODINA AND IR.OZNAKAROKA = P.OZNAKAROKA
WHERE MESTORODJENJA = 'Arandjelovac'
AND NOT EXISTS(
SELECT *
FROM TMP P1
WHERE P1.INDEKS<>D.INDEKS AND
P.OZNAKAROKA=P1.OZNAKAROKA AND P.SKGODINA=P1.SKGODINA AND
P1.PROLAZNOST < P.PROLAZNOST
)
AND PROLAZNOST = (
SELECT MIN(PROLAZNOST)
FROM TMP P1
WHERE P.INDEKS = P1.INDEKS
)
order by d.IME, d.PREZIME;