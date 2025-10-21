create function br_dana(f_indeks integer)
returns integer
return
    case when (
        select DATDIPLOMIRANJA
        from DA.DOSIJE
        where INDEKS = f_indeks
    ) is not null then (
        select days_between(DATDIPLOMIRANJA, DOSIJE.DATUPISA)
        from DA.DOSIJE
        where INDEKS = f_indeks
    ) else 0 end;

values (DA.br_dana(20150069));

values (DA.br_dana(20150109));
