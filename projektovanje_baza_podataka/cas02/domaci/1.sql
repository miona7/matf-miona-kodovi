create table STUDENT_MAST(
    STUDENT_ID int primary key,
    NAME varchar(50),
    ST_CLASS int default 0
);

create table STUDENT_MARKS(
    STUDENT_ID int primary key,
    SUB1 int check (SUB1 >= 0 and SUB1 <= 100),
    SUB2 int check (SUB2 >= 0 and SUB2 <= 100),
    SUB3 int check (SUB3 >= 0 and SUB3 <= 100),
    SUB4 int check (SUB4 >= 0 and SUB4 <= 100),
    SUB5 int check (SUB5 >= 0 and SUB5 <= 100),
    TOTAL int check (TOTAL >= 0 and TOTAL <= 500),
    PER_MARKS int check (PER_MARKS >= 0 and PER_MARKS <= 100),
    GRADE varchar(10),

    constraint fk_id foreign key (STUDENT_ID) references STUDENT_MAST(STUDENT_ID) on delete cascade on update cascade
);

create table STUDENT_LOG(
    LOG_ID serial primary key,
    USER_ID varchar(50) not null,
    DESCRIPTION text
);

create function ADD_RESULTS()
returns trigger as
$$
begin
    new.TOTAL := new.SUB1 + new.SUB2 + new.SUB3 + new.SUB4 + new.SUB5;
    new.PER_MARKS := new.TOTAL / 5;
    new.GRADE := case
              when new.PER_MARKS >= 90 then 'excellent'
              when new.PER_MARKS >= 75 then 'very good'
              when new.PER_MARKS >= 60 then 'good'
              when new.PER_MARKS >= 40 then 'average'
              else 'not promoted' end;
    return new;
end;
$$ language plpgsql;

create trigger ADD_RESULTS
before insert on STUDENT_MARKS
for each row
execute function ADD_RESULTS();

insert into STUDENT_MAST(STUDENT_ID, NAME)
values (1, 'Darko'),
        (2, 'Jovan');

insert into STUDENT_MARKS(STUDENT_ID, SUB1, SUB2, SUB3, SUB4, SUB5)
values (1, 70, 80, 20, 50, 100),
       (2, 80, 100, 100, 100, 30);

select *
from STUDENT_MAST;

select *
from STUDENT_MARKS;