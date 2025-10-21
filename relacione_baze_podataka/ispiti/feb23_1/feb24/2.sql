with budzet_sa_4_istih as (
    select distinct uk.INDEKS indeks, uk.IDPREDMETA predmet, sp.NAZIV program, count(*) br_upisa
    from DA.UPISANKURS uk join DA.DOSIJE d on uk.INDEKS = d.INDEKS
                        join DA.STUDENTSKISTATUS ss on d.IDSTATUSA = ss.ID and ss.NAZIV = 'Budzet'
                        join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
    group by uk.INDEKS, uk.IDPREDMETA, sp.NAZIV
    having count(*) > 4
), pet_istih as (
    select distinct uk.INDEKS indeks, uk.IDPREDMETA predmet, p.NAZIV naziv
    from DA.UPISANKURS uk join DA.PREDMET p on uk.IDPREDMETA = p.ID
                        join DA.ISPIT i on uk.INDEKS = i.INDEKS and i.IDPREDMETA = p.ID
    group by uk.INDEKS, uk.IDPREDMETA, p.NAZIV
    having count(*) = 5
)
select distinct d.INDEKS, d.IME || ' ' || d.PREZIME "Ime i prezime", program "Komentar",
                dayname(DATUPISA) "Naziv dana"
from DA.DOSIJE d join budzet_sa_4_istih b on d.INDEKS = b.indeks
union
select distinct d.INDEKS, d.IME || ' ' || d.PREZIME "Ime i prezime", naziv || ' ' || coalesce(i.OCENA, 5) "Komentar",
                coalesce(dayname(i.DATPOLAGANJA), 'null') "Naziv dana"
from DA.DOSIJE d join pet_istih p on d.INDEKS = p.indeks
        join DA.ISPIT i on d.INDEKS = i.INDEKS and i.IDPREDMETA = p.predmet


