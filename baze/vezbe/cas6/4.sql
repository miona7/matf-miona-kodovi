with br_studenata as (
    select p.NAZIV, p.ID, count(i.INDEKS) br_st
    from DA.PREDMET p left join DA.ISPIT i on p.ID = i.IDPREDMETA and i.STATUS not in ('p', 'n')
    group by p.NAZIV, p.ID
)
select *
from br_studenata;
