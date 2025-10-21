with uslovni as (
    select distinct p.ID, u.NAZIV
    from DA.PREDMET p join DA.USLOVNIPREDMET up on p.ID = up.IDPREDMETA
                        join DA.PREDMET u on u.ID = up.IDUSLOVNOGPREDMETA
), tmp as (
    select p.ID, count(*) br_studenata
    from DA.PREDMET p join DA.ISPIT i on i.IDPREDMETA = p.ID
    group by p.ID
)
select distinct p.ID, p.NAZIV, u.NAZIV,
                case when t.br_studenata <= 30 then 'I kategorija'
                    when t.br_studenata <= 50 then 'II kategorija'
                    else 'III kategorija' end kategorija
from DA.STUDIJSKIPROGRAM sp join DA.PREDMETPROGRAMA pp on sp.ID = pp.IDPROGRAMA and pp.VRSTA = 'izborni'
        join DA.PREDMET p on pp.IDPREDMETA = p.ID join uslovni u on p.ID = u.ID
        join tmp t on t.ID = p.ID
where sp.NAZIV = 'Informatika'
order by p.NAZIV, u.NAZIV desc