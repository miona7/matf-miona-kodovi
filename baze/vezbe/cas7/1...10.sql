create table kandidati_za_upis (
    id integer not null primary key generated always as identity (minvalue 1),
    idprograma integer not null,
    ime varchar(50) not null,
    prezime varchar(50) not null,
    pol char,
    mestorodjenja varchar(50),
    datumprijave date,
    bodovi float(4),
    foreign key fk_smer (idprograma) references DA.STUDIJSKIPROGRAM,
    constraint vr_pol check (pol in ('m', 'z'))
);

insert into kandidati_za_upis (idprograma, ime, prezime, pol, mestorodjenja, datumprijave)
values (103, 'Marko', 'Markovic', 'm', 'Kragujevac', date ('12.11.2020'));

select *
from kandidati_za_upis;

alter table kandidati_za_upis
drop mestorodjenja;

drop table kandidati_za_upis;

alter table kandidati_za_upis
    add constraint vr_bodovi check (bodovi between 0 and 100)
    alter column datumprijave
        set default current_date;

insert into kandidati_za_upis(ime, prezime, pol, idprograma)
values ('Snezana', 'Peric', 'z', 103),
       ('Marija', 'Peric', 'z', 101);

insert into kandidati_za_upis(ime, prezime, pol, idprograma, bodovi)
    select d.IME, d.PREZIME, d.POL, d.IDPROGRAMA, 90
    from DA.DOSIJE d join DA.STUDENTSKISTATUS ss on d.IDSTATUSA = ss.ID
    where ss.NAZIV = 'Ispisan';

delete from kandidati_za_upis
where bodovi is null;

delete from kandidati_za_upis
where (ime, prezime) in (
    select d.IME, d.PREZIME
    from DA.DOSIJE d
    where exists(
        select *
        from DA.ISPIT i
        where i.INDEKS = d.INDEKS and i.STATUS = 'o' and i.OCENA > 5
));

select *
from kandidati_za_upis;

update kandidati_za_upis
    set bodovi = case
                    when bodovi * 1.2 <= 100 then bodovi * 1.2
                    when bodovi is not null then 100 end
where datumprijave >= current_date - 2 days;