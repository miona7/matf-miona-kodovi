l = 0.7; % duzina klatna
r = 0.1; 
m = 0.001; % masa tega
% dinamicka viskoznost
% mi = 1.82*1e-5; % vazduh
mi = 0.00089; % voda
g = 9.81;
theta0 = pi/2; % pocetni ugao
v0 = 30; % pocetna brzina
O = [0 0];
tend = 50;
init = [theta0, v0/l];
B = 2*r*pi*mi; % kad imamo otpor

% anonimna fja koja u sebi ima vektor od 2 fje - sistem koji resavamo
% f = @(t, x) [x(2); -g/l*sin(x(1))]; % kada smo u vakumu
f = @(t, x) [x(2); -B/m*x(2)-g/l*sin(x(1))]; % kada smo u nekoj sredini

% prvi arg = sistem koji treba da resi
% drugi argument = interval
% treci arg = pocetni uslovi
% rezultat = t i x
% t - izdeljeni interval od 0 do tend (sam je izdelio)
% x = x1 + x2
% x1 = vrednosti ugla theta u odgovarajucim trenucima
% x2 = vrednosti ugla theta' u odgovarajucim trenucima
[t, x] = ode45(f, [0, tend], init);

figure(1)
axis(gca, 'equal')
axis([-1 1 -1 1]*l*1.2)
O_centar = viscircles(O, 0.01); % crta tackicu - koordinate + poluprecnik
for i = 1:length(t)
    P = [l*sin(x(i, 1)) -l*cos(x(i, 1))]; % koordinate lopte - gde se loptica nalazi
    lopta = viscircles(P, 0.05);

    % spaja dve tacke koje su zadate x i y koordinatama
    kanap = line([O(1), P(1)], [O(2), P(2)]);

    pause(0.05);

    % i kanap i lopta su objekti
    if i < length(t)
        delete(lopta); 
        delete(kanap);
    end
end