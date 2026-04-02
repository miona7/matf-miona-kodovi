function [x, briter] = nula(x0, tol, iterM)

briter = 0;

while briter < iterM
    x1 = funk(x0);
    briter = briter + 1;
    if abs(x0-x1) <= tol
        disp('dostignuta je tacnost');
    end
    x0 = x1;
end

x = x1;

if briter == iterM
    disp('dostignut je maksimalan broj iteracija');
end