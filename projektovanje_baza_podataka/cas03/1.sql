-- Zadatak 1:
-- U informacionom sistemu jedne kompanije, potrebno je pratiti podatke o zaposlenima.
-- Svaki zaposleni ima svog nadredjenog menadzera, osim u slucaju da je zaposleni zapravo vlasnik kompanije.
-- Za svakog zaposlenog je potrebno cuvati sledece informacije: ID zaposlenog - empid, ime, Username - sqlid,
-- ID nadredjenog menadzera - mgrid, platu - salary (decimalan broj, zaokruzen na 2 decimale), informaciju da li je
-- zaposleni ujedno i menadzer - isMgr (dozvoljene opcije su 'Y' i 'N').
-- Informacije o menadzerima i ostalim zaposlenima cuvati unutar iste tabele 'Profiles'.
-- Menadzer moze videti plate svojih zaposlenih, ali ne i zaposlenih ostalih menadzera, kao ni njihove plate.
-- Napraviti shemu i okidace koji omogucavaju menadzerima da menjaju plate zaposlenima za koje su zaduzeni.

create schema if not exists MANAGEMENT;

create table PROFILES(
    EMPID int primary key,
    NAME varchar(20),
    SQLID varchar(50),
    MGID int,
    SALARY dec(9, 2) check (SALARY >= 0),
    ISMGR char(1) check (ISMGR in ('Y', 'N'))
);

insert into PROFILES
values (0001, 'SuperBoss', 'sboss', NULL, 500000, 'Y'),
       (1001, 'BigBoss', 'bboss', 0001, 200000, 'Y'),
       (1002, 'MySelf', USER, 0001, 250000, 'Y'),
       (2001, 'FirstLine', 'fline', 1001, 100000, 'Y'),
       (2002, 'MiddleMen', 'mmen', 1001, 110000, 'Y'),
       (2003, 'Yeti', 'yeti', 1002, 90000, 'Y'),
       (2004, 'BigFoot', 'bfoot', 1002, 80000, 'N'),
       (3001, 'TinyToon', 'ttoon', 2001, 50000, 'N'),
       (3002, 'Mouse', 'Mouse', 2001, 40000, 'N'),
       (3003, 'Whatsisname','wname', 2002, 45000, 'N'),
       (3004, 'Hasnoclue', 'hclue', 2002, 38000, 'N'),
       (3005, 'Doesallwork','dwork', 2003, 15000, 'N');

-- Dati podaci se mogu posmatrati kao stablo. U podstablu cvora koji predstavlja menadzera, nalaze se svi njegovi zaposleni.
-- Menadzer X moze biti nadredjen menadzeru Y, koji je nadredjen radniku Z. Tada je menadzer X nadredjen i radniku Z.
-- Zbog prirode ovakve relacije, nije dovoljno dohvatiti prve potomke nekog cvora, vec je potrebno obici rekurzivno i
-- potomke njegovih direktnih potomaka, tj. potrebno je izvrsiti pretragu stabla.
-- Mehanizam pretrage stabla u slucaju ovako zadatih podataka, moze se izvrsiti pomocu **rekurzivnog SQL upita**, koji po nacinu
-- izvrsavanja lici na BFS pretragu stabla.

-- Napraviti pogled koji omogucava prikaz plate menadzera ciji je sqlid=USER i svih njegovih zaposlenih.

-- rekurzivni upiti se uvek sastoje od dva dela koji su spojeni sa UNION ALL:
-- 1. sidro (inicijalizacija) - izvrsava se samo jednom na samom pocetku
-- 2. rekurzivni korak - izvrsava se iznova i iznova sve dok pronalazi nove redove

create view MANAGERS_EMPLOYEES(EMPID, SALARY, LEVEL) as
with recursive REC(EMPID, SALARY, LEVEL) as ( -- pravimo privremenu tabelu koja se zove REC
    -- inicijalizacija
    select EMPID, SALARY, 0
    from PROFILES
    where SQLID = USER

    UNION ALL

    -- rekurzivni korak -> dodajemo ostale koji su podredjeni menadzerima iz pomocne tabele
    select P.EMPID, P.SALARY, LEVEL - 1
    from PROFILES as P, REC as R
    where P.MGID = R.EMPID -- nadju radnika P ciji je menadzer zapravo onaj radnik R kojeg smo pronasli u prethodnom koraku
        and LEVEL > -100 -- guard -> sprecava beskonacnu petlju
) select EMPID, SALARY, LEVEL from REC; -- glavni upit

-- Napraviti pogled koji nam omogucava da vidimo sledece:
-- empid, neposredno iz PROFILES
-- name, neposredno iz PROFILES
-- mgrname, ime neposredno nadredjenog
-- salary, plata ako je nas zaposleni, inace NULL
-- sqlid, neposredno iz PROFILES
-- ismgr, neposredno iz PROFILES

create view MANAGERS_VIEW(EMPID, NAME, MGRNAME, SALARY, SQLID, ISMGR) as
select P.EMPID, P.NAME,M.NAME, ME.SALARY, P.SQLID, P.ISMGR
from PROFILES as P left outer join MANAGERS_EMPLOYEES ME on P.EMPID = ME.EMPID left outer join PROFILES M on P.MGID = M.EMPID;

create function INSERT_EMPLOYEE()
returns trigger as
$$
declare MGRID int;
        ISMGR char(1);
begin
    -- 1) Na osnovu imena menadzera (mgrname) treba da zakljucimo ID nadredjenog
    select EMPID, ISMGR
    into MGRID, ISMGR
    from PROFILES
    where new.MGRNAME = P.NAME;

    -- 2) Provera da li je mgrid jedan od naših zaposlenih
    -- 3) Provera da li je nadredjeni menadzer
    if MGRID not in (select EMPID from MANAGERS_EMPLOYEES) or ISMGR <> 'Y' then
        raise exception 'Not Authorized!';
    end if;

    -- 4) Ako je sve ok, unosimo novog zaposlenog
    insert into PROFILES(EMPID, NAME, SQLID, MGID, SALARY, ISMGR)
    values (new.EMPID, new.NAME, new.SQLID, new.MGID, new.SALARY, new.ISMGR);

    return null;

end;
$$ language plpgsql;

create trigger INSERT_EMPLOYEE
instead of insert on MANAGERS_VIEW
for each row
execute function INSERT_EMPLOYEE();

-- Posto azuriramo podatke koji su u pogledu, mogu se desiti odredjeni specijalni slucajevi koje je potrebno obraditi.
-- Treba da proverimo sledece (za radnika kojeg menjamo):
  -- 1) Da li po starim podacima radnik pripada skupu nasih radnika?
  -- 2) Da li po novim podacima radnik pripada skupu nasih radnika?
  -- 3) Da li menjamo radnika koji nismo mi?
-- Sta jos moze da bude problematicno?
  -- 4) Da li je neko ko ima podredjene dobio vrednost za ismgr = 'N'?
  -- 5) Da li je novi nadredjeni naseg radnika menadzer?

