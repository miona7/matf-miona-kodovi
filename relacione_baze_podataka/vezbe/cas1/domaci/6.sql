select INDEKS "Student", year(DATUPISA) "Godina upisa"
from DA.DOSIJE
where year(DATUPISA) not between 2013 and 2016;
