select d.INDEKS, d.IME, d.PREZIME, ug.SKGODINA, ug.DATUPISA
from DA.DOSIJE d join DA.UPISGODINE ug on d.INDEKS = ug.INDEKS
order by d.INDEKS desc, ug.SKGODINA