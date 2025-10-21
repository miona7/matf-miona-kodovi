select d.INDEKS, d.IME, d.PREZIME, p.NAZIV, i.OCENA
from DA.DOSIJE d join DA.ISPIT i on d.INDEKS = i.INDEKS and STATUS = 'o' and OCENA > 5
    join DA.PREDMET p on i.IDPREDMETA = p.ID