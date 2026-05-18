drop shema if exists AUTOSKOLA cascade;
create schema AUTOSKOLA;
set search_path to AUTOSKOLA;

create table POLAZNIK(
    ID serial primary key,
    IME varchar(30) not null,
    PREZIME varchar(70) not null,
    IZDATA_DOZVOLA boolean not null default false
);

-- moguce je napraviti tabelu bez primarnog kljuca
create table ISPIT(
    ID_POLAZNIKA int not null,
    DATUM_POLAGANJA date not null default current_date,
    TIP_ISPITA varchar(10) not null check (TIP_ISPITA in ('teorijski', 'prakticni')),
    BODOVI smallint not null check (BODOVI between 0 and 100),
    ISHOD varchar(10), -- not null check (ISHOD in ('polozio', 'pao')),

    constraint fk_polaznik foreign key (ID_POLAZNIKA) references POLAZNIK(ID) on delete cascade on update cascade
);

create table STATISTIKE(
    TIP_ISPITA varchar(10) not null,
    BROJ_POLAGANJA smallint not null default 0 check (BROJ_POLAGANJA >= 0),
    BROJ_POLOZENIH smallint not null default 0 check (BROJ_POLAGANJA >= 0)
);

insert into POLAZNIK(IME, PREZIME)
values ('Pera', 'Peric'),
       ('Mika', 'Mikic'),
       ('Zika', 'Zikic');

select * from POLAZNIK;

-- a) Prilikom umetanja ili azuriranja novog ispita, potrebno je automatski odrediti
--    njegov ishod. Ishod moze biti 'polozio' ili 'pao', pri cemu je polaznik:
--    - polozio TEORIJSKI ispit ukoliko je osvojio bar 85 bodova;
--    - polozio PRAKTICNI ispit ukoliko je osvojio manje od 15 bodova (kazneni poeni).

create function ODREDI_I_DODAJ_ISHOD_ISPITA()
returns trigger as
$$
begin
    if (new.TIP_ISPITA = 'teorijski' and new.BODOVI >= 85) or (new.TIP_ISPITA = 'prakticni' and new.BODOVI < 15) then
       -- operator dodela :=
       new.ISHOD := 'polozio';
    else
        new.ISHOD := 'pao';
    end if;
    return new;
end;
$$ language plpgsql;

-- u before okidacima voditi racuna o povratnoj vrednosti funkcije
create trigger ODREDI_I_DODAJ_ISHOD_ISPITA
before insert or update on ISPIT
for each row
execute function ODREDI_I_DODAJ_ISHOD_ISPITA();

insert into ISPIT(SIFRA_POLAZNIKA, DATUM, TIP_ISPITA, BODOVI)
values (1, '2025-10-10', 'teorijski', 92);

insert into ISPIT(SIFRA_POLAZNIKA, DATUM, TIP_ISPITA, BODOVI)
values (1, '2025-10-10', 'prakticni', 17);

select * from ISPIT;

update ISPIT
set BODOVI = 14
where ID_POLAZNIKA = 1 AND TIP_ISPITA = 'prakticni';

select * from ISPIT;

-- b) Potrebno je validirati izdavanje vozackih dozvola. Polazniku se dozvola moze
--    izdati samo ukoliko je prethodno polozio i teorijski, i prakticni ispit. U
--    suprotnom, potrebno je prijaviti gresku prilikom pokusaja izdavanja dozvole.

create function VALIDIRAJ_IZDAVANJE_DOZVOLE()
returns trigger as
$$
-- declare -> definisanje promenljive za zadati blok
declare POLOZIO_TEORIJSKI boolean
        POLOZIO_PRAKTICNI boolean
begin
    POLOZIO_TEORIJSKI := exists (
        select *
        from ISPIT
        where ID_POLAZNIKA = new.ID and TIP_ISPITA = 'teorijski' and ISHOD = 'polozio'
    );

    POLOZIO_PRAKTICNI := exists (
        select *
        from ISPIT
        where ID_POLAZNIKA = new.ID and TIP_ISPITA = 'prakticni' and ISHOD = 'polozio'
    )

    if new.IZDATA_DOZVOLA = true and (not POLOZIO_TEORIJSKI or not POLOZIO_PRAKTICNI) then
       raise exception 'Da bi se izdala dozvola, polaznik % % mora poloziti i teorijski i prakticni!', new.IME, new.PREZIME;
    end if;
    return new;
end;
$$ language plpgsql;

create trigger VALIDIRAJ_IZDAVANJE_DOZVOLE
before insert or update on POLAZNIK
for each row
execute function VALIDIRAJ_IZDAVANJE_DOZVOLE();

-- c) U posebnoj tabeli STATISTIKE se prate statistike o polaganjima teorijskih
--    i prakticnih ispita (konkretno, prati se broj polaganja i broj polozenih
--    ispita). Prilikom bilo kakvih operacija nad tabelom ISPIT, potrebno je azurirati i odgovarajuce statistike.
--    Pretpostaviti da tabela STATISTIKE vec sadrzi odgovarajuce redove za teorijske i prakticne ispite.
