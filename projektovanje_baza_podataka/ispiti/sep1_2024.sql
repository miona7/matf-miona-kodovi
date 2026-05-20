-- Date su relacije: Kursevi (sifra_kursa, naziv, espb, sifra_uslovnog_kursa, sifra_profesora)
-- Profesori (sifra_profesora, ime, prezime, katedra)
-- Definisati okidac nad relacijom Kursevi kojim se dozvoljava unos samo onih kurseva ciji broj espb poena ima pozitivnu vrednost manju od -- 20.

create table PROFESOR(
    SIFRA_PROFESORA serial primary key,
    IME varchar(20) not null,
    PREZIME varchar(20) not null,
    KATEDRA varchar(50) not null
);

create table KURSEVI(
    SIFRA_KURSA serial primary key,
    NAZIV varchar(50) not null,
    ESPB int not null,
    SIFRA_USLOVNOG_KURSA int,
    SIFRA_PROFESORA int,

    constraint fk_sifra_uk foreign key (SIFRA_USLOVNOG_KURSA) references KURSEVI(SIFRA_KURSA) on delete cascade on update cascade,
    constraint fk_sifra_profesora foreign key (SIFRA_PROFESORA) references PROFESOR(SIFRA_PROFESORA) on delete cascade on update cascade
);

create function PROVERI_ESPB()
returns trigger as
$$
begin
    if new.ESPB >= 20 then
       raise exception 'ESPB mora biti manji od 20!';
    end if;
    return new;
end;
$$ language plpgsql;

create trigger PROVERI_ESPB
before insert on KURSEVI
for each row
execute function PROVERI_ESPB();

insert into PROFESOR
values (1, 'Pera', 'Peric', 'informatika'),
       (2, 'Mita', 'Mitic', 'matematika');

insert into KURSEVI
values (1, 'Programiranje 1', 8, NULL, 1),
       (2, 'Programiranje 2', 8, 1, 1);

select *
from KURSEVI;

insert into KURSEVI
values (3, 'Linearna algebra', 22, NULL, 2);

select *
from KURSEVI;