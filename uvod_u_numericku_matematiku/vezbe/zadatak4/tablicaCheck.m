function t = tablicaCheck()

tablica;

r = all(diff(X) > 0);
m = all(diff(Y) > 0) || all(diff(Y) < 0);

t = r && m;

if r == 0
    disp('X nije rastuci')
end

if m == 0
    disp('Y nije monoton')
end