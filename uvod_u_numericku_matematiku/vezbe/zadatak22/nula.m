function [I, Y, x] = nula(x0, xF, tol, iterM)

tablica;
koef = Njutn1();
h = X(2) - X(1);
f = @(x) polyval(koef, (x - X(1))/h);

briter = 0;
Y = [];

while briter < iterM
    x1 = x0 - (f(x0) / (f(xF) - f(x0))) * (xF - x0);
    briter = briter + 1;
    Y = [Y f(x1)];
    
    greska = abs(x1-x0);
    if greska < tol
        break;
    end

    x0 = x1;
end

if briter == iterM && greska < tol
    disp('Dostignut je max br iter i zadovoljena tacnost');
else 
    if greska < tol
        disp('Zadovoljena tacnost');
    else 
        disp('dostignut broj max iter');
    end
end


I = 1:briter;
x = x1;
