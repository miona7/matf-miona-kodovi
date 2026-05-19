create table EMP_DETAILS(
    EMPLOYEE_ID serial primary key,
    FIRST_NAME varchar(50),
    LAST_NAME varchar(50),
    EMAIL varchar(50),
    PHONE_NUMBER varchar(15),
    HIRE_DATE date,
    JOB_ID int,
    SALARY int check (SALARY >= 0),
    COMMISSION_PCT dec(5, 2) check (COMMISSION_PCT >= 0.00 and COMMISSION_PCT <= 100.00)
);

create function CHANGE_SALARY()
returns trigger as
$$
begin
    if new.SALARY > 20000 then
        new.COMMISSION_PCT := 0.1;
    else
        new.COMMISSION_PCT := 0.5;
    end if;
    return new;
end;
$$ language plpgsql;

create trigger CHANGE_SALARY
before insert on EMP_DETAILS
for each row
execute function CHANGE_SALARY();

insert into EMP_DETAILS(FIRST_NAME, LAST_NAME, EMAIL, PHONE_NUMBER, HIRE_DATE, JOB_ID, SALARY)
values ('Darko', 'Jovanovic', 'darko.jovanovic@hotmail.com', '123-456', '2020-03-01', 1000, 15000),
       ('Janko', 'Bozic', 'janko1993@hotmail.com', '113-496', '2018-08-12', 1000, 25000);

select *
from EMP_DETAILS;