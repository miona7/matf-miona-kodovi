-- ZADATAK:
-- a) Kreirati shemu Prodavnica koja ce skladistiti sledece relacije u vidu tabela:
--    Dostava(ID,SIFRA_KUPCA,JMBG_DOSTAVLJACA,NAPOMENA,ADRESA,STATUS,DATUM_IZMENE,BROJ_POKUSAJA)
--    Dostavljac(JMBG,BROJ_VOZACKE,KATEGORIJA,IME,PREZIME)
--    Kupac(SIFRA,IME,PREZIME,ADRESA,TELEFON,MEJL)
--    Ukoliko shema sa zadatim imenom vec postoji, obrisati je pre ponovnog kreiranja.

-- b) Prilikom kreiranja tabela koje imaju strani kljuc, integritet stranog kljuca u slucaju azuriranja obezbediti kaskadnim izvrsavanjem.

-- c) Prodavnica mora imati poznate informacije o imenu, prezimenu, adresi i telefonu kupca, dok imejl adreas ne mora biti poznata.
--    Obezbediti da dva kupca ne mogu imati isti telefon niti da dva dostavljaca mogu imati isti broj vozacke dozvole.

-- d) Prilikom evidentiranja dostave, njen status moze biti - kreirana, spakovana, otkazana ili izvrsena. Obezbediti da status po formiranju podrazumevano bude kreirana.
--    Da bi dostavu bilo moguce obaviti, potrebno je da bude poznata adresa kao i datum izmene statusa. Takodje, broj pokusaja je nenegativan ceo broj koji je podrazumevano 0 i ne moze biti veci od 2.

-- e) Napisati naredbu nezavisnu od naredbe za kreiranje tabele Kupac, kojom se toj tabeli dodaje uslov da imejl adresa mora biti poznata.
-- Napisati naredbu kojom se brise kolona kategorija vec kreirane tabele Dostavljac.

drop shema if exists PRODAVNICA cascaded;
create shema PRODAVNICA;
set search_path to PRODAVNICA;

create table KUPAC(
    SIFRA serial primary key,
    IME varchar(30) not null,
    PREZIME varchar(50) not null,
    ADRESA varchar(100) not null,
    TELEFON int not null unique, -- unique -> vrednost kolone mora biti jedinstvena na nivou citave tabele
    MEJL varchar(100)
);

create table DOSTAVLJAC(
    JMBG int primary key,
    BROJ_VOZACKE int not null unique,
    KATEGORIJA varchar(2),
    IME varchar(30) not null,
    PREZIME varchar(70) not null
);

create table DOSTAVA(
    ID serial primary key,
    SIFRA_KUPCA int not null,
    JMBG_DOSTAVLJACA int not null,
    NAPOMENA text,
    ADRESA varchar(100) not null,
    STATUS varchar(10) default 'kreirana' check (STATUS in ('kreirana', 'spakovana', 'otkazana', 'izvrsena')),
    DATUM_IZMENE date not null,
    BROJ_POKUSAJA smallint default 0 check (BROJ_POKUSAJA between 0 and 2),

    constraint fk_kupac foreign key (SIFRA_KUPCA) references KUPAC(SIFRA) on update cascade,
    constraint fk_dostavljac foreign key (JMBG_DOSTAVLJACA) references DOSTAVLJAC(JMBG) on update cascade
);

alter table KUPAC
add check (MEJL is not null);

alter table DOSTAVLJAC
drop column KATEGORIJA;

-- TODO: istestirati