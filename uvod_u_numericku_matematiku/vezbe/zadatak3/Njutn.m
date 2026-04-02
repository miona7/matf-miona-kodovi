function nj = Njutn(x)

t = tablicaCheck();
if t == 0
    disp('Nisu ispunjeni uslovi')
end

p = polozaj(x);
if p == 1
    nj = Njutn1(x);
else 
    if p == 2
        nj = Njutn2(x);
    else 
        disp('Tacka je na sredini koristite Lagranza')
    end
end