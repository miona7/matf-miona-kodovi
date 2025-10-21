select INDEKS, IDPREDMETA, OCENA,
       case when OCENA = 10 then 'deset'
            when OCENA = 9 then 'devet'
            when OCENA = 8 then 'osam'
            when OCENA = 7 then 'sedam'
            when OCENA = 6 then 'sest'
            else 'nepolozen' end "Ocena slovima"
from DA.ISPIT
where STATUS not in ('p', 'n')