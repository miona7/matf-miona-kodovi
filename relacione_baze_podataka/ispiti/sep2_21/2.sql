with bar_3_priznata as (
    select INDEKS indeks, sum(ESPB) priznati_espb
    from DA.PRIZNATISPIT
    group by INDEKS
    having count(*) >= 3
), polozeni_upisani_predmeti as (
    select uk.INDEKS indeks, sum(ESPB) polozeno_espb
    from DA.UPISANKURS uk join DA.ISPIT i on uk.INDEKS = i.INDEKS and i.IDPREDMETA = uk.IDPREDMETA
                            join DA.PREDMET p on i.IDPREDMETA = p.ID
    where STATUS = 'o' and OCENA > 5
    group by uk.INDEKS
    having (uk.INDEKS, count(*)) in (select uk1.INDEKS, count(*) from DA.UPISANKURS uk1 group by uk1.INDEKS)
)
select bp.indeks, polozeno_espb + priznati_espb "ukupan broj espb",
       priznati_espb * 100.0 / (priznati_espb + polozeno_espb) "procenat priznatih",
       polozeno_espb * 100.0 / (priznati_espb + polozeno_espb) "procenat polozenih"
from bar_3_priznata bp join polozeni_upisani_predmeti pp on bp.indeks = pp.indeks
order by polozeno_espb;

