function L = legendre(n)

if n == 0
    L = 1;
else 
    p = [1 0 -1];
    pn = p;
    for i = 2 : n
        pn = conv(pn, p);
    end
    
    for i = 1 : n
        pn = polyder(pn);
    end
    
    L = 1 / (2^n * factorial(n)) * pn;
end