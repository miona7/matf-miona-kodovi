select IME, PREZIME
from DA.DOSIJE
where IME <> 'Marko' and IME <> 'Veljko' and IME <> 'Ana'
order by PREZIME desc, IME