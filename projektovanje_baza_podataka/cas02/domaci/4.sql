drop schema if exists PUBLISHING_HOUSE;
create schema PUBLISHING_HOUSE;

create table P(
    P_SIF serial primary key,
    IME varchar(50) not null,
    BR_NASLOVA int not null default 0,
    DRZAVA varchar(50) not null
);

create table I(
    I_SIF serial primary key,
    NAZIV varchar(50) not null,
    STATUS varchar(10) not null,
    DRZAVA varchar(50) not null
);

create table K(
    K_SIF serial primary key,
    NASLOV varchar(50) not null,
    OBLAST varchar(50) not null
);

create table KP(
    K_SIF int,
    P_SIF int,
    R_BROJ int,

    primary key (K_SIF, P_SIF, R_BROJ),
    constraint fk_k_sif foreign key (K_SIF) references K(K_SIF) on delete cascade on update cascade,
    constraint fk_p_sif foreign key (P_SIF) references P(P_SIF) on delete cascade on update cascade
);

create table KI(
    K_SIF int,
    I_SIF int,
    IZDANJE int,
    GODINA int not null,
    TIRAZ int not null,

    primary key (K_SIF, I_SIF, IZDANJE),
    constraint fk_k_sif foreign key (K_SIF) references K(K_SIF) on delete cascade on update cascade,
    constraint fk_i_sif foreign key (I_SIF) references I(I_SIF) on delete cascade on update cascade
);

create function UPDATE_TABLE_P()
returns trigger as
$$
begin
    if tg_op = 'INSERT' then
        update P
        set BR_NASLOVA = BR_NASLOVA + 1
        where P_SIF = new.P_SIF;
    elsif tg_op = 'DELETE' then
        update P
        set BR_NASLOVA = BR_NASLOVA - 1
        where P_SIF = old.P_SIF;
    elsif tg_op = 'UPDATE' then
        if old.P_SIF is distinct from new.P_SIF then
            update P
            set BR_NASLOVA = BR_NASLOVA - 1
            where P_SIF = old.P_SIF;

            update P
            set BR_NASLOVA = BR_NASLOVA + 1
            where P_SIF = new.P_SIF;
        end if;
    end if;
    return null;
end;
$$ language plpgsql;

create trigger UPDATE_TABLE_P
after insert or delete or update on KP
for each row
execute function UPDATE_TABLE_P();

insert into P(IME, DRZAVA)
values ('Borko', 'Srbija'),
       ('Dzon', 'Engleska');

insert into I(NAZIV, STATUS, DRZAVA)
values ('RSIzdavac', 'aktivan', 'Srbija'),
       ('KK', 'neaktivan', 'Srbija');

insert into K(NASLOV, OBLAST)
values ('Biologija za sedmake', 'Obrazovanje'),
       ('Matematika za osmi razred osnovne skole', 'Obrazovanje'),
       ('English for Slavs', 'Obrazovanje - Education');

insert into KP
values (1, 1, 1), (2, 1, 2), (3, 2, 1);

select *
from P;

select *
from K;

select *
from KP;

delete from KP
where K_SIF = 2;

select *
from P;