function nula = polov(tol)

tablica;

a = X(1);
b = X(end);

if funk(a) * funk(b) > 0
    error('Nisu ispunjeni uslovi');
end

if funk(a) == 0
    nula = a;
else
    if funk(b) == 0
        nula = b;
    else
        while b - a > tol 
            x = (a+b)/2;

            if funk(x) == 0
                nula = x;
                break;
            end

            if funk(a) * funk(x) < 0
                b = x;
            else 
                a = x;
            end

        end
        nula = (a+b) / 2;
    end
end