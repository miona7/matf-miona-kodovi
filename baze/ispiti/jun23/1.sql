select case when d.POL = 'm' then 'Student ' else 'Studentkinja ' end || d.IME || ' ' || d.PREZIME "Student/kinja",
       d.INDEKS, sp.NAZIV, substr(nk.NAZIV, 1, locate(' ', nk.NAZIV) - 1) "Nivo studija"
from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
                join DA.NIVOKVALIFIKACIJE nk on sp.IDNIVOA = nk.ID
where year(d.DATUPISA) = 2015