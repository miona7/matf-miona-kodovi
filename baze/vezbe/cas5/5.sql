select count(distinct OCENA)
from DA.ISPIT
where OCENA > 5;

select count(distinct nullif(OCENA, 5))
from DA.ISPIT;