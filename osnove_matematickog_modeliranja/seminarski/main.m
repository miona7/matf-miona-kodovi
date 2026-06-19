clear; clc; close all;

%  0. KONSTANTE I EKSPERIMENTALNI PODACI

g = 9.81;

% Eksperimentalni podaci iz postavke zadatka
t_exp = [0,     0.347, 0.47,  0.519, 0.582, 0.65,  0.674, 0.717, 0.766, ...
         0.823, 0.87,  1.031, 1.193, 1.354, 1.501, 1.726, 1.873];
x_exp = [0,     0.61,  1.00,  1.22,  1.52,  1.83,  2.00,  2.13,  2.44,  ...
         2.74,  3.00,  4.00,  5.00,  6.00,  7.00,  8.50,  9.50];

n = length(t_exp);  


%  1. MODEL (i): BEZ OTPORA  (F_o = 0)

x_m1 = @(t) 0.5 .* g .* t.^2;

reziduali_m1 = x_m1(t_exp) - x_exp;
mse_m1       = mean(reziduali_m1.^2);


%  2. MODEL (ii): OTPOR PROPORCIONALAN BRZINI  (F_o = k*v)

% Funkcije modela parametrizovane sa alpha
v_m2 = @(a, t) (g ./ a) .* (1 - exp(-a .* t));
x_m2 = @(a, t) (g ./ a) .* t + (g ./ a.^2) .* (exp(-a .* t) - 1);

% Funkcija greske po parametru alpha
mse_m2_fun = @(a) mean((x_m2(a, t_exp) - x_exp).^2);

% Numericki optimum: fminbnd trazi minimum na (lb, ub)
alpha_m2_opt = fminbnd(mse_m2_fun, 1e-4, 500);
mse_m2       = mse_m2_fun(alpha_m2_opt);
v_inf_m2     = g / alpha_m2_opt;   


%  3. MODEL (iii): OTPOR PROPORCIONALAN KVADRATU BRZINE  (F_o = k*v^2)

v_m3 = @(a, t) sqrt(g ./ a) .* tanh(sqrt(g .* a) .* t);
x_m3 = @(a, t) (1 ./ a) .* log(cosh(sqrt(g .* a) .* t));

mse_m3_fun   = @(a) mean((x_m3(a, t_exp) - x_exp).^2);

alpha_m3_opt = fminbnd(mse_m3_fun, 1e-4, 500);
mse_m3       = mse_m3_fun(alpha_m3_opt);
v_inf_m3     = sqrt(g / alpha_m3_opt); 


%  4. VREDNOSTI ZA UNOS U TABELU

fprintf('Vertikalni pad sa razlicitim otporom sredine\n');

fprintf('Model (i): F_o = 0 (bez otpora)\n');
fprintf('MSE = %.6f m^2\n\n', mse_m1);

fprintf('Model (ii): F_o = k*v (otpor ~ brzina)\n');
fprintf('Optimalno k/m (alpha)   = %.6f s^(-1)\n', alpha_m2_opt);
fprintf('Terminalna brzina v_inf = %.4f m/s\n', v_inf_m2);
fprintf('MSE                     = %.6f m^2\n\n', mse_m2);

fprintf('Model (iii): F_o = k*v^2 (otpor ~ kvadrat brzine)\n');
fprintf('Optimalno k/m (alpha)   = %.6f m^(-1)\n', alpha_m3_opt);
fprintf('Terminalna brzina v_inf = %.4f m/s\n', v_inf_m3);
fprintf('MSE                     = %.6f m^2\n\n', mse_m3);

% Identifikacija najboljeg modela
mse_svi   = [mse_m1, mse_m2, mse_m3];
[~, best] = min(mse_svi);
nazivi    = {'(i) F_o = 0', '(ii) F_o = kv', '(iii) F_o = kv^2'};
fprintf('>>> Najmanji MSE ima model: %s\n\n', nazivi{best});


%  5. SLIKA 1: POREDENJE PREDENOG PUTA SA EKSPERIMENTALNIM PODACIMA

t_plot = linspace(0, max(t_exp) * 1.04, 1200); 

fig1 = figure('Name', 'Predeni put - poredjenje', ...
              'Position', [80, 80, 900, 560]);

hold on; grid on; box on;

% Eksperimentalni podaci
plot(t_exp, x_exp, ...
    'ko', 'MarkerSize', 8, 'LineWidth', 1.5, ...
    'MarkerFaceColor', [0.9 0.9 0.9], ...
    'DisplayName', 'Eksperimentalni podaci');

% Model (i)
plot(t_plot, x_m1(t_plot), ...
    'b--', 'LineWidth', 2.2, ...
    'DisplayName', 'Model (i): F_o = 0');

% Model (ii)
plot(t_plot, x_m2(alpha_m2_opt, t_plot), ...
    'r-', 'LineWidth', 2.2, ...
    'DisplayName', sprintf('Model (ii): F_o = kv,   k/m = %.4f s^{-1}', alpha_m2_opt));

% Model (iii)
plot(t_plot, x_m3(alpha_m3_opt, t_plot), ...
    'Color', [0.1 0.7 0.1], 'LineStyle', '-', 'LineWidth', 2.2, ...
    'DisplayName', sprintf('Model (iii): F_o = kv^2, k/m = %.4f m^{-1}', alpha_m3_opt));

xlabel('Vreme  t  [s]',         'FontSize', 13, 'Interpreter', 'tex');
ylabel('Predeni put  x  [m]',   'FontSize', 13, 'Interpreter', 'tex');
title('Vertikalni pad: poredjenje modela sa eksperimentalnim podacima', ...
      'FontSize', 13);
legend('Location', 'northwest', 'FontSize', 11);
xlim([0, max(t_exp)*1.04]);
ylim([0, max(x_exp)*1.12]);

hold off;

saveas(fig1, 'fig_poredjenje.pdf');
fprintf('Sacuvana slika: fig_poredjenje.pdf\n');


%  6. SLIKA 2: PROFIL BRZINE ZA SVA TRI MODELA

fig2 = figure('Name', 'Profil brzine', ...
              'Position', [100, 60, 900, 520]);

hold on; grid on; box on;

% Model (i): v = g*t  
t_m1_plot = linspace(0, max(t_exp)*0.7, 800);  
plot(t_m1_plot, g .* t_m1_plot, ...
    'b--', 'LineWidth', 2.2, ...
    'DisplayName', 'Model (i): F_o = 0  (prikazano do 70% opsega)');

% Model (ii): v(t)
plot(t_plot, v_m2(alpha_m2_opt, t_plot), ...
    'r-', 'LineWidth', 2.2, ...
    'DisplayName', sprintf('Model (ii): v_{\\infty} = %.2f m/s', v_inf_m2));

% Model (iii): v(t)
plot(t_plot, v_m3(alpha_m3_opt, t_plot), ...
    'Color', [0.1 0.7 0.1], 'LineStyle', '-', 'LineWidth', 2.2, ...
    'DisplayName', sprintf('Model (iii): v_{\\infty} = %.2f m/s', v_inf_m3));

% Terminalne brzine (horizontalne isprekidane linije)
yline(v_inf_m2, 'r:', 'LineWidth', 1.4, 'HandleVisibility', 'off');
yline(v_inf_m3, ':', 'Color', [0.1 0.7 0.1], ...
      'LineWidth', 1.4, 'HandleVisibility', 'off');

% Oznake terminalnih brzina
t_ann = max(t_exp) * 0.97;
text(t_ann, v_inf_m2 + 0.3, ...
     sprintf('v_{\\infty}^{(ii)} = %.2f m/s', v_inf_m2), ...
     'Color', 'r', 'FontSize', 10, 'HorizontalAlignment', 'right', ...
     'Interpreter', 'tex');
text(t_ann, v_inf_m3 - 0.6, ...
     sprintf('v_{\\infty}^{(iii)} = %.2f m/s', v_inf_m3), ...
     'Color', [0.1 0.7 0.1], 'FontSize', 10, ...
     'HorizontalAlignment', 'right', 'Interpreter', 'tex');

xlabel('Vreme  t  [s]',      'FontSize', 13, 'Interpreter', 'tex');
ylabel('Brzina  v  [m/s]',   'FontSize', 13, 'Interpreter', 'tex');
title('Profil brzine za tri modela vertikalnog pada', 'FontSize', 13);
legend('Location', 'northwest', 'FontSize', 11);
xlim([0, max(t_exp)*1.04]);

hold off;

saveas(fig2, 'fig_brzine.pdf');
fprintf('Sacuvana slika: fig_brzine.pdf\n');


%  7. SLIKA 3: REZIDUALNE GRESKE

reziduali_m2 = x_m2(alpha_m2_opt, t_exp) - x_exp;
reziduali_m3 = x_m3(alpha_m3_opt, t_exp) - x_exp;

fig3 = figure('Name', 'Rezidualne greske', ...
              'Position', [120, 40, 960, 520]);

hold on; grid on; box on;

% Nulta linija 
plot(t_exp([1,end]), [0 0], 'k-', 'LineWidth', 1, ...
     'HandleVisibility', 'off');

% Model (i)
plot(t_exp, reziduali_m1, ...
    'bs--', 'MarkerSize', 8, 'LineWidth', 1.5, 'MarkerFaceColor', 'b', ...
    'DisplayName', 'Model (i): F_o = 0');

% Model (ii)
plot(t_exp, reziduali_m2, ...
    'r^-', 'MarkerSize', 8, 'LineWidth', 1.5, 'MarkerFaceColor', 'r', ...
    'DisplayName', sprintf('Model (ii): F_o = kv, k/m = %.4f', alpha_m2_opt));

% Model (iii)
plot(t_exp, reziduali_m3, ...
    'v-', 'Color', [0.1 0.7 0.1], 'MarkerSize', 8, 'LineWidth', 1.5, ...
    'MarkerFaceColor', [0.1 0.7 0.1], ...
    'DisplayName', sprintf('Model (iii): F_o = kv^2, k/m = %.4f', alpha_m3_opt));

xlabel('Vreme  t  [s]',                   'FontSize', 13, 'Interpreter', 'tex');
ylabel('Rezidualna greska  r_i  [m]',      'FontSize', 13, 'Interpreter', 'tex');
title('Rezidualne greske: x_{model}(t_i) - x_i^{exp}', ...
      'FontSize', 13, 'Interpreter', 'tex');
legend('Location', 'northwest', 'FontSize', 11);
xlim([0, max(t_exp)*1.04]);

hold off;

saveas(fig3, 'fig_reziduali.pdf');
fprintf('Sacuvana slika: fig_reziduali.pdf\n\n');


%  8. TABELA ZA UNOS U RAD (MSE + parametri)

fprintf('VREDNOSTI ZA TABELU 2 U RADU:\n');
fprintf('Model (i)   | k/m = ---           | MSE = %.6f m^2\n', mse_m1);
fprintf('Model (ii)  | k/m = %.6f s^-1 | MSE = %.6f m^2\n', alpha_m2_opt, mse_m2);
fprintf('Model (iii) | k/m = %.6f m^-1 | MSE = %.6f m^2\n', alpha_m3_opt, mse_m3);

fprintf('Sva izracunavanja su zavrsena. Slike su sacuvane u radnom folderu.\n');
