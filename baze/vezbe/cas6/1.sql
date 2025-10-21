with kategorija as (
    select case when ESPB < 6 then 'lak'
                when ESPB <= 8 then 'srednji'
                else 'tezak' end tezina
    from DA.PREDMET
)
select tezina, count(*)
from kategorija
group by tezina