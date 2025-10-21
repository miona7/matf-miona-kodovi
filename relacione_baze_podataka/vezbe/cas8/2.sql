select d.IME, d.PREZIME, p.NAZIV
from DA.DOSIJE d join DA.PREDMETPROGRAMA pp on d.IDPROGRAMA = pp.IDPROGRAMA and pp.VRSTA = 'obavezan'
    join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID and sp.NAZIV = 'Informatika'
    join DA.NIVOKVALIFIKACIJE nk on sp.IDNIVOA = nk.ID and nk.NAZIV like 'Osnovne%'
    join DA.PREDMET p on pp.IDPREDMETA = p.ID
where year(d.DATUPISA) = 2015 and not exists(
    select *
    from DA.ISPIT i
    where i.INDEKS = d.INDEKS and i.IDPREDMETA = p.ID and i.STATUS = 'o' and i.OCENA > 5
)