function t = tablicaCheck()

tablica;

h = X(2) - X(1);
e = all(abs(diff(X) - h) < 0.0001);
r = all(diff(X) > 0);

if e == 0
    disp('Tablica nije ekvidistantna')
end

if r == 0
    disp('X nije rastuci')
end


t = e && r;