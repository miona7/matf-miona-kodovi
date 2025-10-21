create table upis_na_master(
    indeks int not null,
    zeljeni_smer varchar(50) not null,
    ocena_za_upis float,
    primary key (indeks, zeljeni_smer)
)@

-- drop trigger unos_upis_na_master @

create trigger unos_upis_na_master
    before insert on upis_na_master
    referencing new as n
    for each row
    when (n.INDEKS not in (
                    select d.INDEKS
                    from DA.DOSIJE d join DA.STUDIJSKIPROGRAM sp on d.IDPROGRAMA = sp.ID
                                    join DA.NIVOKVALIFIKACIJE nk on sp.IDNIVOA = nk.ID
                    )
        )
    begin atomic
        signal sqlstate '75000' ('Student nije na osnovnim studijama');
    end @

select *
from upis_na_master @

insert into upis_na_master
select d.INDEKS, sp.NAZIV, avg(i.OCENA * 1.0) / (select count(*)
                                                                        from DA.UPISGODINE ug
                                                                        where ug.INDEKS = d.INDEKS)
from DA.DOSIJE d join DA.STUDENTSKISTATUS ss on d.IDSTATUSA = ss.ID and STUDIRA = 1
                join DA.ISPIT i on d.INDEKS = i.INDEKS and STATUS = 'o' and OCENA > 5
                join DA.PREDMET p on p.ID = i.IDPREDMETA
                join DA.STUDIJSKIPROGRAM sp on sp.ID = d.IDPROGRAMA
                join DA.NIVOKVALIFIKACIJE nk on nk.ID = sp.IDNIVOA and nk.NAZIV like 'Osnovne%'
group by d.INDEKS, sp.NAZIV, OBIMESPB
having (OBIMESPB - sum(ESPB)) between 5 and 30
@

merge into upis_na_master unm
using (
    select d.INDEKS indeks, sp.NAZIV smer, avg(i.OCENA * 1.0) / (select count(*)
                                                    from DA.UPISGODINE ug
                                                    where ug.INDEKS = d.INDEKS) prosek
    from DA.DOSIJE d join DA.STUDENTSKISTATUS ss on d.IDSTATUSA = ss.ID
                join DA.ISPIT i on d.INDEKS = i.INDEKS and STATUS = 'o' and OCENA > 5
                join DA.PREDMET p on p.ID = i.IDPREDMETA
                join DA.STUDIJSKIPROGRAM sp on sp.ID = d.IDPROGRAMA
                join DA.NIVOKVALIFIKACIJE nk on nk.ID = sp.IDNIVOA and nk.NAZIV like 'Osnovne%'
    where ss.NAZIV = 'Diplomirao' and year(d.DATDIPLOMIRANJA) = 2019
    group by d.INDEKS, sp.NAZIV
) as t on unm.INDEKS = t.indeks and unm.zeljeni_smer = t.smer
when matched then
    update
    set unm.ocena_za_upis = t.prosek
when not matched then
    insert values (t.indeks, t.smer, t.prosek)
@

drop table upis_na_master @
