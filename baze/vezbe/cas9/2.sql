create function prosek(prosek float)
returns varchar(4000)
return
    with tmp as (
        select INDEKS, decimal(avg(OCENA*1.0), 4, 2) p
        from DA.ISPIT
        where STATUS = 'o' and OCENA > 5
        group by INDEKS
    )
    select count(*) || ':' || listagg(INDEKS, '-')
    from tmp
    where decimal(p, 4, 2) = prosek;

values (DA.PROSEK(9.96));