-- Date su relacije Artikal(id, naziv, cena) i Sekcija(naziv_artikla,naziv_sekcije)
-- Mehanizmom okidaca obezbediti da kolona cena u dinarima u tabeli Artikal uvek ima pozitivnu vrednost.

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

create function PROVERI_CENU()
returns trigger as
$$
begin
    if new.CENA < 0 then
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

insert into ARTIKAL(NAZIV, CENA)
values ('secer', -12);

select *
from ARTIKAL;