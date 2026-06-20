-- Date su sledeće relacije:
-- Učesnici (jmbg, ime, prezime)
-- Ugovori (šifra, jmbg_kupca, jmbg_prodavca, ukupna_vrednost, datum_zaključenja)
-- Uplate (šifra_ugovora, redni_broj, iznos)

-- Kreirati bazu podataka sa nazivom kupoprodajni_ugovori koja sadrži prethodne relacije.
-- Ukoliko već postoji baza sa istim nazivom, obrisati je pre kreiranja nove. 
-- Integritet stranog ključa u slučaju brisanja obezbediti kaskadnim izvršavanjem, a ažuriranje zabraniti.
-- Sve informacije moraju biti poznate, sem datuma zaključenja u ugovoru, koji može biti izostavljen.
-- Obezbediti da se ne može napraviti ugovor izmedju iste osobe u ulozi prodavca i kupca, kao
-- i to da ukupna vrednost ugovora i iznos uplata moraju biti pozitivni brojevi.

drop schema if exists kupoprodajni_ugovori cascade;
create schema kupoprodajni_ugovori;
set search_path to kupoprodajni_ugovori;

create table Učesnici(
    jmbg char(13) primary key,
    ime varchar(50) not null,
    prezime varchar(70) not null
);

create table Ugovori(
    šifra serial primary key,
    jmbg_kupca char(13) not null,
    jmbg_prodavca char(13) not null,
    ukupna_vrednost real not null check (ukupna_vrednost > 0),
    datum_zaključenja date,

    constraint fk_kupac foreign key (jmbg_kupca) references Učesnici(jmbg) on delete cascade on update restrict,
    constraint fk_prodavac foreign key (jmbg_prodavca) references Učesnici(jmbg) on delete cascade on update restrict,
    
    check (jmbg_kupca <> jmbg_prodavca)
);

create table Uplate(
    šifra_ugovora serial not null,
    redni_broj serial not null,
    iznos real not null check (iznos > 0),

    primary key(šifra_ugovora, redni_broj),

    constraint fk_sifra foreign key (šifra_ugovora) references Ugovori(šifra) on delete cascade on update restrict
);