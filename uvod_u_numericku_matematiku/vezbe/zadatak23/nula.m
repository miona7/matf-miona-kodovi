function x = nula(tol, iterM)

tablica;

koef = Lagranz();

f = @(x) polyval(koef, x);

x0 = X(1);
x1 = X(end);

iter = 0;

while iter < iterM
    x2 = x1 - (f(x1) / (f(x0) - f(x1))) * (x0 - x1);
    iter = iter + 1;

    if abs(x2 - x1) < tol
        disp('zadovoljena tacnost');
        break;
    end

    x0 = x1;
    x1 = x2;
end

x = x2;

if iter == iterM
    disp('dostignut max br iter');
end