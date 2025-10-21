select *
from DA.ISPITNIROK
where OZNAKAROKA <= all (
    select OZNAKAROKA
    from DA.ISPITNIROK
) and SKGODINA <= all (
    select SKGODINA
    from DA.ISPITNIROK
);

