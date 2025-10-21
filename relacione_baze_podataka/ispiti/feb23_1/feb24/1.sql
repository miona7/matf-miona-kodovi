select p1.NAZIV, p2.NAZIV
from DA.PREDMET p1 join DA.PREDMET p2 on p1.ID < p2.ID
where p1.ESPB = p2.ESPB and p1.NAZIV like '___ri%' and length(p2.NAZIV) > 4
    and exists(
        select *
        from DA.ISPIT i1
        where i1.IDPREDMETA = p1.ID and i1.STATUS = 'o' and i1.OCENA > 5
            and exists(
                select *
                from DA.ISPIT i2
                where i2.INDEKS = i1.INDEKS and i2.IDPREDMETA = p2.ID
                        and i2.STATUS = 'o' and i2.OCENA > 5
                        and i2.SKGODINA = i1.SKGODINA
        )
)
order by p1.NAZIV, p2.NAZIV;
