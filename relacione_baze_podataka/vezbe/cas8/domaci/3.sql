create function inicijali(f_indeks integer)
returns varchar(3)
return
    case when exists(
        select *
        from DA.DOSIJE d
        where d.INDEKS = f_indeks
    ) then (select substr(d.IME, 1, 1) || substr(d.PREZIME, 1, 1)
            from DA.DOSIJE d
            where d.INDEKS = f_indeks)
    else 'XXX' end;


drop function inicijali;

values DA.inicijali(20150069);