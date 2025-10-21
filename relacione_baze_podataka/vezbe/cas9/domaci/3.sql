select d.INDEKS, sp.OZNAKA, sp.OBIMESPB,
       sum(case when i.STATUS ='o' and i.OCENA > 5 then p.ESPB else 0 end) broj_polozenih_espb,
       sum(case when i.STATUS ='o' and i.OCENA > 5 then p.ESPB else 0 end) * 1.0 / sp.OBIMESPB * 1.0 procenat_polozenih_espb,
       sum(case when pp.VRSTA = 'obavezan' then p.ESPB else 0 end) broj_espb_obaveznih,
       sum(case when pp.VRSTA = 'obavezan' and i.STATUS ='o' and i.OCENA > 5 then p.ESPB else 0 end) broj_espb_polozenih_obaveznih,
       sum(case when pp.VRSTA = 'obavezan' and i.STATUS ='o' and i.OCENA > 5 then p.ESPB else 0 end) * 1.0 / sum(case when pp.VRSTA = 'obavezan' then p.ESPB else 0 end) * 1.0 procenat_polozenih_obaveznih
from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
    join DA.PREDMETPROGRAMA pp on sp.ID = pp.IDPROGRAMA
    join DA.NIVOKVALIFIKACIJE nk on sp.IDNIVOA = nk.ID and nk.NAZIV like 'Osnovne%'
    join DA.ISPIT i on d.INDEKS = i.INDEKS
    join DA.PREDMET p on i.IDPREDMETA = p.ID
group by d.INDEKS, sp.OZNAKA, sp.OBIMESPB, sp.OBIMESPB
order by procenat_polozenih_espb;

WITH polozeni AS (
    SELECT d.INDEKS, sp.OZNAKA, sp.OBIMESPB, p.ID AS IDPREDMETA, p.ESPB,
           pp.VRSTA,
           CASE WHEN i.OCENA > 5 AND i.STATUS = 'o' THEN 1 ELSE 0 END AS polozen
    FROM DA.DOSIJE d
    JOIN DA.STUDIJSKIPROGRAM sp ON d.IDPROGRAMA = sp.ID
    JOIN DA.NIVOKVALIFIKACIJE nk ON sp.IDNIVOA = nk.ID
    JOIN DA.UPISANKURS uk ON uk.INDEKS = d.INDEKS
    JOIN DA.PREDMET p ON uk.IDPREDMETA = p.ID
    LEFT JOIN DA.ISPIT i ON i.INDEKS = d.INDEKS AND i.IDPREDMETA = p.ID
    LEFT JOIN DA.PREDMETPROGRAMA pp ON pp.IDPROGRAMA = sp.ID AND pp.IDPREDMETA = p.ID
    WHERE nk.NAZIV LIKE 'Osnovne%'
)

SELECT
    INDEKS,
    OZNAKA,
    OBIMESPB,
    SUM(CASE WHEN polozen = 1 THEN ESPB ELSE 0 END) AS broj_polozenih_espb,
    DECIMAL(SUM(CASE WHEN polozen = 1 THEN ESPB ELSE 0 END) * 1.0 / OBIMESPB, 5, 2) AS procenat_polozenih_espb,

    SUM(CASE WHEN VRSTA = 'obavezan' THEN ESPB ELSE 0 END) AS espb_obaveznih,
    SUM(CASE WHEN VRSTA = 'obavezan' AND polozen = 1 THEN ESPB ELSE 0 END) AS espb_polozenih_obaveznih,
    CASE
        WHEN SUM(CASE WHEN VRSTA = 'obavezan' THEN ESPB ELSE 0 END) = 0 THEN NULL
        ELSE DECIMAL(SUM(CASE WHEN VRSTA = 'obavezan' AND polozen = 1 THEN ESPB ELSE 0 END) * 1.0
                     / SUM(CASE WHEN VRSTA = 'obavezan' THEN ESPB ELSE 0 END), 5, 2)
    END AS procenat_polozenih_obaveznih

FROM polozeni
GROUP BY INDEKS, OZNAKA, OBIMESPB
ORDER BY procenat_polozenih_espb;
