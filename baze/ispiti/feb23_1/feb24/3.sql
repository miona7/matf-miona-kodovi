create table smerovi (
    id integer not null primary key,
    naziv char(100),
    nivo char(10),
    studenti smallint,
    prosek float,
    constraint vr_nivo check (nivo in ('osnovne', 'master', 'doktorske'))
);

create function to_cm(duzina integer, mera char(1))
returns smallint
return
    case
        when mera = 'd' then duzina * 10
        when mera = 'm' then duzina * 100
        when mera = 'k' then duzina * 1000 * 100
        else -1
    end;


insert into smerovi(id, naziv, studenti)
select sp.ID, sp.NAZIV, count(*)
from DA.STUDIJSKIPROGRAM sp join DA.NIVOKVALIFIKACIJE nk on sp.IDNIVOA = nk.ID
    join DA.DOSIJE d on d.IDPROGRAMA = sp.ID
where nk.NAZIV like 'Osnovne%'
group by sp.ID, sp.NAZIV;


select *
from SMEROVI
where studenti < 100 and prosek > 9.0;


merge into smerovi s
using (
    select sp.ID, sp.NAZIV,
           case
               when sp.IDNIVOA = 1 then 'osnovne'
                when sp.IDNIVOA = 2 then 'master'
                when sp.IDNIVOA = 3 then 'doktorske'
            end nivo, count(*) studenti, avg(OCENA * 1.0) prosek

    from DA.STUDIJSKIPROGRAM sp join DA.DOSIJE d on sp.ID = d.IDPROGRAMA
                                join DA.ISPIT i on d.INDEKS = i.INDEKS and STATUS = 'o' and OCENA > 5
    group by sp.ID, sp.NAZIV, sp.IDNIVOA
) as tmp on tmp.ID = s.id
when matched then
    update
    set s.prosek = tmp.prosek
when not matched then
    insert
    values (tmp.ID, tmp.NAZIV, tmp.nivo, tmp.studenti, tmp.prosek);

delete from smerovi
where studenti < 100 and prosek > 9.0;

drop table smerovi;