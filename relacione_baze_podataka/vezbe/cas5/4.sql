select distinct OCENA, nullif(OCENA, 5)
from DA.ISPIT;

select distinct case when OCENA = 5 then NULL else OCENA end
from DA.ISPIT