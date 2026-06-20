-- Date su relacije Artikal(id, naziv, cena) i Sekcija(naziv_artikla,naziv_sekcije)

create table ARTIKAL(
    ID serial primary key,
    NAZIV varchar(50) not null unique,
    CENA int
);

create table SEKCIJA(
    NAZIV_SEKCIJE varchar(50) primary key,
    NAZIV_ARTIKLA varchar(50) not null,

    constraint fk_naziv_artikla foreign key (NAZIV_ARTIKLA) references ARTIKAL(NAZIV) on delete cascade on update cascade
);

-- a) Mehanizmom okidaca obezbediti da kolona cena u dinarima u tabeli Artikal uvek ima pozitivnu vrednost

create function PROVERI_CENU()
returns trigger as
$$
begin
    if new.CENA <= 0 then
       raise exception 'Cena ne sme da bude negativna';
    end if;
    return new;
end;
$$ language plpgsql;

create trigger PROVERI_CENU
before insert on ARTIKAL
for each row
execute function PROVERI_CENU();

insert into ARTIKAL(NAZIV, CENA)
values ('brasno', 50), ('so', 100);

select *
from ARTIKAL;

-- insert into ARTIKAL(NAZIV, CENA)
-- values ('secer', -12);

select *
from ARTIKAL;

-- b) Napisati naredbu kojom se definiše pogled artikli u evrima koji ispisuje id, naziv i cenu_u_evrima svih 
-- artikala iz tabele Artikal (1 evro = 100 dinara)

create or replace view ARTIKLI_U_EVRIMA(ID, NAZIV, CENA_U_EVRIMA) as
select ID, NAZIV, CENA / 100.0
from Artikal;

select *
from ARTIKLI_U_EVRIMA;

-- c) Obezbediti unos artikla (id = 1, naziv = 'Čokolada', cena = 2.2) u pogled artikli_u_evrima

create or replace function UNESI_ARTIKAL_U_POGLED()
returns trigger as $$
declare CENA int;
begin
    CENA := new.CENA_U_EVRIMA * 100.00;

    insert into ARTIKAL
    values(new.ID, new.NAZIV, CENA);

    return new;
end;
$$language plpgsql;

create or replace trigger UNESI_ARTIKAL_U_POGLED
instead of insert on ARTIKLI_U_EVRIMA
for each row
execute function UNESI_ARTIKAL_U_POGLED();

insert into ARTIKLI_U_EVRIMA
values (10, 'Čokolada', 2.2);

select * 
from ARTIKAL;

select * 
from ARTIKLI_U_EVRIMA;

insert into ARTIKAL
values (20, 'Ogroman lilihip', 1999.99);

insert into SEKCIJA
values ('Slatkisi', 'Ogroman lilihip');

-- d) Definisati pogled koji ispisuje id, naziv, cenu i sekciju svih artikala čija je cena u dinarima veća od 1500
create or replace view CENA_VECA_OD_1500(ID, NAZIV, CENA, SEKCIJA) as
select a.ID, a.NAZIV, a.CENA, s.NAZIV_SEKCIJE
from ARTIKAL a join SEKCIJA s on a.NAZIV = s.NAZIV_ARTIKLA
where a.CENA > 1500;

select *
from CENA_VECA_OD_1500;

-- e) Definisati okidač nad pogledom iz dela pod d) za operaciju brisanja i objasniti da li je bez njega
-- brisanje iz tako definisanog pogleda nemoguće
create or replace function OBRISI()
returns trigger as $$
begin
    delete from ARTIKAL
    where ID = old.ID;

    return old;
end;
$$ language plpgsql;

create or replace trigger OBRISI
instead of delete on CENA_VECA_OD_1500
for each row
execute function OBRISI();

select *
from CENA_VECA_OD_1500;

delete from CENA_VECA_OD_1500
where SEKCIJA = 'Slatkisi';

select *
from CENA_VECA_OD_1500;

-- nije moguce zato sto u pogledu imamo spajanje tabela
