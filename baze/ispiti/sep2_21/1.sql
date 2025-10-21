with najveca_ocena as (
    select IDPREDMETA predmet, max(OCENA) ocena
    from DA.ISPIT
    where STATUS = 'o' and OCENA > 5
    group by IDPREDMETA
)
select NAZIV, coalesce(substr(IME, 1, 1) || substr(PREZIME, 1, 1), 'nema') "Inicijali", OCENA
from DA.PREDMET p left join DA.ISPIT i on p.ID = i.IDPREDMETA and STATUS = 'o' and
                                          OCENA in (select ocena from najveca_ocena where p.ID = predmet)
                    left join DA.DOSIJE d on i.INDEKS = d.INDEKS
where NAZIV like '_o_e%';
