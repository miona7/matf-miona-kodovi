drop schema if exists BANKA cascade;
create schema BANKA;
set search_path to BANKA;

create table RACUN(
    BROJ_RACUNA int primary key,
    STANJE_NA_RACUNU real not null default 0.00,
    DNEVNI_LIMIT real not null default 5000.00
);

create table TRANSAKCIJA(
    SIFRA serial primary key,
    BROJ_RACUNA_POSILJAOCA int not null,
    BROJ_RACUNA_PRIMAOCA int not null,
    IZNOS real not null check (IZNOS > 0.00),
    DATUM date not null default current_date,

    constraint fk_posiljalac foreign key (BROJ_RACUNA_POSILJAOCA) references RACUN(BROJ_RACUNA) on delete restrict on update restrict,
    constraint fk_primalac foreign key (BROJ_RACUNA_PRIMAOCA) references RACUN(BROJ_RACUNA) on delete restrict on update restrict,

    constraint ck_racuni check (BROJ_RACUNA_POSILJAOCA <> BROJ_RACUNA_PRIMAOCA)
);

insert into RACUN(BROJ_RACUNA, STANJE_NA_RACUNU)
values (123, 10000.00),
       (456, 20000.00);

-- a) Trenutno se, prilikom kreiranja novih transakcija, stanja na racunima ne azuriraju.
--   Implementirati okidac kojim se, nakon svake transakcije, shodno njoj azuriraju stanja racuna posiljaoca i primaoca.

create function AZURIRAJ_STANJE_NA_RACUNU_NAKON_TRANSAKCIJE()
returns trigger as
$$
begin
    update RACUN
    set STANJE_NA_RACUNU = STANJE_NA_RACUNU + new.IZNOS
    where BROJ_RACUNA = new.BROJ_RACUNA_PRIMAOCA;

    update RACUN
    set STANJE_NA_RACUNU = STANJE_NA_RACUNU - new.IZNOS
    where BROJ_RACUNA = new.BROJ_RACUNA_POSILJAOCA;

    return null;
end;
$$ language plpgsql;

create trigger AZURIRAJ_STANJE_NA_RACUNU_NAKON_TRANSAKCIJE
after insert on TRANSAKCIJA
for each row
execute function AZURIRAJ_STANJE_NA_RACUNU_NAKON_TRANSAKCIJE();

select *
from RACUN;

insert into TRANSAKCIJA(BROJ_RACUNA_POSILJAOCA, BROJ_RACUNA_PRIMAOCA, IZNOS)
values (123, 456, 2000.00),
       (456, 123, 1000.00);

select *
from RACUN;

-- b) Trenutno je moguce kreirati transakciju kojom bi stanje na racunu posiljaoca otislo u negativan iznos.
--   Implementirati okidac kojim se onemogucava kreiranje ovakvih transakcija.

create function PROVERI_VALIDNOST_TRANSAKCIJE()
returns trigger as
$$
declare IZNOS_NA_RACUNU real;
begin
     IZNOS_NA_RACUNU := (
        select STANJE_NA_RACUNU
        from RACUN
        where BROJ_RACUNA = new.BROJ_RACUNA_POSILJAOCA
    );

    if new.IZNOS > IZNOS_NA_RACUNU then
        raise exception 'Nemate dovoljno novca na racunu!';
    end if;
    return new;
end;
$$ language plpgsql;

create trigger PROVERI_VALIDNOST_TRANSAKCIJE
before insert on TRANSAKCIJA
for each row
execute function PROVERI_VALIDNOST_TRANSAKCIJE();

-- insert into TRANSAKCIJA(BROJ_RACUNA_POSILJAOCA, BROJ_RACUNA_PRIMAOCA, IZNOS)
-- values (123, 456, 200000.00);

-- c) Svaki racun ima svoj dnevni limit. Ukoliko neka transakcija premasuje dnevni limit racuna posiljaoca,
--   potrebno je izmeniti, tj. ograniciti njen iznos do preostalog dnevnog limita.
--   Ukoliko je dnevni limit potpuno istrosen, u potpunosti zabraniti izvrsavanje transakcije.

create function OGRANICI_NA_DNEVNI_LIMIT_PRI_NOVOJ_TRANSAKCIJI()
returns trigger as
$$
declare DNEVNI_LIMIT_POSILJAOCA real;
        POTROSENO_U_DANU real;
begin
    DNEVNI_LIMIT_POSILJAOCA := (
        select DNEVNI_LIMIT
        from RACUN
        where BROJ_RACUNA = new.BROJ_RACUNA_POSILJAOCA
    );

    POTROSENO_U_DANU := (
        select sum(IZNOS)
        from TRANSAKCIJA
        where BROJ_RACUNA_POSILJAOCA = new.BROJ_RACUNA_POSILJAOCA
    );

    if DNEVNI_LIMIT_POSILJAOCA = POTROSENO_U_DANU then
       raise exception 'Dnevni limit korisnika % je istrosen!', new.BROJ_RACUNA_POSILJAOCA;
    elsif POTROSENO_U_DANU + new.IZNOS > DNEVNI_LIMIT_POSILJAOCA then
        raise notice 'Iznos transakcije premasuje dnevni limit od % dinara korisnika % ::: '
          'Iznos ce biti umanjen sa % na % dinara', DNEVNI_LIMIT_POSILJAOCA, new.BROJ_RACUNA_POSILJAOCA, new.IZNOS, DNEVNI_LIMIT_POSILJAOCA - POTROSENO_U_DANU;
        new.IZNOS := DNEVNI_LIMIT_POSILJAOCA - POTROSENO_U_DANU;
    end if;
    return new;
end;
$$ language plpgsql;

create trigger OGRANICI_NA_DNEVNI_LIMIT_PRI_NOVOJ_TRANSAKCIJI
before insert on TRANSAKCIJA
for each row
execute function OGRANICI_NA_DNEVNI_LIMIT_PRI_NOVOJ_TRANSAKCIJI();

insert into TRANSAKCIJA(BROJ_RACUNA_POSILJAOCA, BROJ_RACUNA_PRIMAOCA, IZNOS)
values (123, 456, 5000.00);

select *
from TRANSAKCIJA;

insert into TRANSAKCIJA(BROJ_RACUNA_POSILJAOCA, BROJ_RACUNA_PRIMAOCA, IZNOS)
values (123, 456, 1000.00);

-- d) Potrebno je onemoguciti brisanje ili azuriranje vec kreiranih transakcija.

create function ONEMOGUCI_BRISANJE_I_AZURIRANJE_TRANSAKCIJA()
returns trigger as
$$
begin
    raise exception 'Zabranjeno % transakcije', tg_op;
end;
$$ language plpgsql;

create trigger ONEMOGUCI_BRISANJE_I_AZURIRANJE_TRANSAKCIJA
before update or delete on TRANSAKCIJA
for each statement -- VODITI RACUNA, za for each row neki okidaci nece da se izvrse jer ne gadjaju nijedan red
execute function ONEMOGUCI_BRISANJE_I_AZURIRANJE_TRANSAKCIJA();

-- update TRANSAKCIJA
-- set IZNOS = IZNOS + 100.00
-- where SIFRA = -1; -- sa FOR EACH ROW, ova naredba ne bi izbacila izuzetak jer ne gadja nijedan red

update TRANSAKCIJA
set IZNOS = 0
where SIFRA = 1;

delete from TRANSAKCIJA
where SIFRA = 1;