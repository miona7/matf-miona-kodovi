create function dan(datum date)
returns varchar(50)
return
    case
        when dayofweek(datum) = 2 then 'Monday'
        when dayofweek(datum) = 3 then 'Tuesday'
        when dayofweek(datum) = 4 then 'Wednesday'
        when dayofweek(datum) = 5 then 'Thursday'
        when dayofweek(datum) = 6 then 'Friday'
        else 'Weekend' end;

drop function dan;

values (DA.dan(current_date))
