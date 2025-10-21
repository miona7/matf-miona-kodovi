create function f(f_pol char)
returns varchar(4000)
return
    case when lower(f_pol) in ('z', 'm') then (
        select listagg(distinct IME, ',') within group (order by IME)
        from DA.DOSIJE
        where POL = lower(f_pol)
    ) else 'Pol ne moze da bude ' || f_pol end;

values (DA.f('z'));

values (DA.f('m'));

values (DA.f('o'));
