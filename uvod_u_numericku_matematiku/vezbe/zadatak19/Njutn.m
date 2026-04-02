function x = Njutn(x0, y, tol)

funkcija;

F = sym(f);
F1 = diff(F); 
F = matlabFunction(F1);  % f'

f = @(x) f(x) - y;

iter = 0;

while iter < 100
    x1 = x0 - f(x0) / F(x0);
    iter = iter + 1;

    if abs(x1 - x0) < tol
        break;
    end

    x0 = x1;
end

if iter == 100
    disp('Dostignut maksimalan broj iteracija');
end

x = x1;