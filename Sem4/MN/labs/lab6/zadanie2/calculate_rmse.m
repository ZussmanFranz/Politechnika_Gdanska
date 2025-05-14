function [dates, y, rmse_values, M, c, ya] = calculate_rmse()
% 1) Wyznacza pierwiastek błędu średniokwadratowego w zależności od stopnia
%    aproksymacji wielomianowej danych przedstawiających produkcję energii.
% 2) Wyznacza i przedstawia na wykresie aproksymację wielomianową wysokiego
%    stopnia danych przedstawiających produkcję energii.
% Dla kraju C oraz źródła energii S:
% dates - wektor energy_2025.C.S.Dates (daty pomiaru produkcji energii)
% y - wektor energy_2025.C.S.EnergyProduction (poziomy miesięcznych produkcji energii)
% rmse_values(i,1) - RMSE wyznaczony dla wektora y i wielomianu i-tego stopnia
%     Rozmiar kolumnowego wektora wynosi length(y)-1.
% M - stopień wielomianu aproksymacyjnego przedstawionego na wykresie
% c - współczynniki wielomianu aproksymacyjnego przedstawionego na wykresie:
%       c = [c_M; ...; c_1; c_0]
% ya - wartości wielomianu aproksymacyjnego wyznaczone dla punktów danych
%       (rozmiar wektora ya powinien być taki sam jak rozmiar wektora y)

    M = 90; % stopień wielomianu aproksymacyjnego (dla wykresu)

    load energy_2025

    dates = []; % dates = energy_2025.C.S.Dates; % TODO
    y = []; % y = energy_2025.C.S.EnergyProduction; % TODO

    N = numel(y);
    degrees = 1:N-1;

    x = linspace(0,1,N)';

    rmse_values = zeros(numel(degrees),1);

    % Oblicz RMSE dla każdego stopnia
    for m = degrees
        % TODO:

        % rmse_values(m) = 
    end

    % Aproksymacja wielomianu wysokiego stopnia (dla wykresu)
    c = polyfit_qr(x, y, M);
    c = c(end:-1:1); % odwrócenie kolejności wektora c: dostosowanie do polyval

    ya = polyval(c, x);

    % TODO:
    % Wykresy

end

function c = polyfit_qr(x, y, M)
    x_col = x(:); % Upewnienie się, że x jest wektorem kolumnowym
    y_col = y(:); % Upewnienie się, że y jest wektorem kolumnowym
    
    N_pts = numel(x_col); % Liczba punktów danych

    A = zeros(N_pts, M+1); % Prealokacja macierzy
    for k = 0:M % k jest potęgą x, od 0 do M
        A(:, k+1) = x_col.^k;
    end
    

    [Q1, R1] = qr(A, 0); 
    
    c = R1 \ (Q1.' * y_col);
end
