create table STUDENT_MAST(
    STUDENT_ID int primary key,
    NAME varchar(50),
    ST_CLASS int default 0
);

create table STUDENT_LOG(
    LOG_ID serial primary key,
    USER_ID varchar(50) not null,
    DESCRIPTION text
);

create function CHECK_CLASS()
returns trigger as
$$
begin
    if new.ST_CLASS < old.ST_CLASS then
        raise exception 'New class must be higher then old class!';
    end if;
    return new;
end;
$$ language plpgsql;

create trigger CHECK_CLASS
before update on STUDENT_MAST
for each row
execute function CHECK_CLASS();

create function ADD_VALUES_IN_STUDENT_LOG_ON_UPDATE()
returns trigger as
$$
begin
    insert into STUDENT_LOG(USER_ID, DESCRIPTION)
    values (SESSION_USER, FORMAT('Change informations about student "%s (%s)", change: %s -> %s',
                                 old.NAME, old.STUDENT_ID, old.ST_CLASS, new.ST_CLASS));
    return new;
end;
$$ language plpgsql;

create trigger ADD_VALUES_IN_STUDENT_LOG_ON_UPDATE
after update on STUDENT_MAST
for each row
execute function ADD_VALUES_IN_STUDENT_LOG_ON_UPDATE();

create function ADD_VALUES_IN_STUDENT_LOG_ON_DELETE()
returns trigger as
$$
begin
    insert into STUDENT_LOG(USER_ID, DESCRIPTION)
    values (SESSION_USER, FORMAT('Deleted student "%s (%s)"', old.NAME, old.STUDENT_ID));
    return old;
end;
$$ language plpgsql;

create trigger ADD_VALUES_IN_STUDENT_LOG_ON_DELETE
after delete on STUDENT_MAST
for each row
execute function ADD_VALUES_IN_STUDENT_LOG_ON_DELETE();

insert into STUDENT_MAST
values (1, 'Darko', 6),
        (2, 'Jovan', 7);

-- azuriranje koje ce proci
update STUDENT_MAST
set ST_CLASS = 7
where NAME = 'Darko';

-- azuriranje koje ce izbaciti gresku zbog smanjenja razreda
-- update STUDENT_MAST
-- set ST_CLASS = 6
-- where NAME = 'Jovan';

delete from STUDENT_MAST
where NAME = 'Jovan';

select *
from STUDENT_MAST;

select *
from STUDENT_LOG;
