-- DDL -> Data Definiton Language
-- koristi se za definisanje i upravljanje strukturom baze podataka -> kreiranje, menjanje, brisanje objekata tj. tabela, shema, pogleda...

-- 1. create -> kreiranje objekata

-- kreiranje sheme -> objekti baze podataka se mogu smestiti unutar zadate sheme
create schema if not exists FAKULTET;
-- postavlja podrazumevanu shemu
set search_path to FAKULTET;

create table STUDENT(
    INDEKS int primary key,
    IME varchar(30) not null,
    PREZIME varchar(50) not null,
    DATUM_RODJENJA date default current_date
);

insert into STUDENT
values (1332022, 'Miona', 'Sretenovic', '2003-09-18'),
       (1232022, 'Pera', 'Peric', '2002-04-28'),
       (0042021, 'Ana', 'Anic', '2002-05-16');

select *
from STUDENT;

-- 2. drop -> brisanje objekata
drop table if exists PREDMET cascade; -- cascade -> brise i sve objekte koji zavise od tabele predmet

create table PREDMET(
    -- serial = int ali se automatski inkrementira
    ID serial primary key,
    NAZIV varchar(50) not null,
    -- ukoliko je ogranicenje u istom redu, onda u ogranicenju smemo da referisemo samo na kolonu koja se nalazi u tom redu, ali ne moramo
    ESPB int check (ESPB between 1 and 30) -- ogranicenje
);

insert into PREDMET(NAZIV, ESPB)
values ('Projektovanje baza podataka', 6),
       ('Programiranje 1', 8),
       ('Analiza 2', 6);

insert into PREDMET
values (5, 'AWS - Rivian', 2);

select *
from PREDMET;

-- naredna za brisanje svih redova u tabeli PREDMET, nije isto sto i drop!
-- delete from PREDMET where true;

-- primer: kreirati tabelu ISPIT, koja cuva informacije o id predmeta koji je polagao student sa odredjenim indeksom, kao i datum polaganja i ocenu koju je dobio
create table ISPIT(
    INDEKS int not null,
    ID_PREDMETA int not null,
    DATUM_POLAGANJA date not null,
    -- smallint -> stedimo memoriju
    OCENA smallint check (OCENA between 5 and 10),

    primary key (INDEKS, ID_PREDMETA),
    -- imenovano ogranicenje za strani kljuc
    constraint fk_student foreign key (INDEKS) references STUDENT(INDEKS),
    constraint fk_predmet foreign key (ID_PREDMETA) references PREDMET(ID)
);

insert into ISPIT
values (1332022, 2, '2023-01-11', 10),
       (1332022, 3, '2024-02-25', 10);

select *
from ISPIT;

-- 3. alter -> omogucava izmenu vec postojeceg objekta

-- omogucava naknadno dodavanje, brisanje ili menjanje kolona i ogranicenja
alter table ISPIT
add column TRAJANJE_U_CASOVIMA int; -- vestacki primer

select *
from ISPIT;