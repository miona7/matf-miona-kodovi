create function br_rokova(f_indeks integer)
returns integer
return
    select count(distinct i.OZNAKAROKA || i.SKGODINA)
    from DA.ISPIT i
    where i.INDEKS = f_indeks and i.STATUS = 'o' and i.OCENA > 5;

select count(distinct i.OZNAKAROKA || i.SKGODINA)
from DA.ISPIT i
where i.INDEKS = 20150069 and i.STATUS = 'o' and i.OCENA > 5;

values (DA.br_rokova(20150069));