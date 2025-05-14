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

    % --- Parametry ---
    M = 99;

    % --- Wczytanie danych ---
    load ../energy_2025

    country_name = 'Poland'; 
    source_name = 'Coal';   

    if isfield(energy_2025, country_name) && isfield(energy_2025.(country_name), source_name)
        data_struct = energy_2025.(country_name).(source_name);
        if isfield(data_struct, 'Dates') && isfield(data_struct, 'EnergyProduction')
            dates = data_struct.Dates;
            y = data_struct.EnergyProduction;
        else
            error(['Wybrana struktura danych dla kraju: ' country_name ' i źródła: ' source_name ...
                   ' nie zawiera wymaganych pól ''Dates'' lub ''EnergyProduction''.']);
        end
    else
        error(['Wybrane dane dla kraju: ' country_name ' i źródła: ' source_name ...
               ' nie istnieją w pliku energy_2025.mat. Sprawdź dostępne opcje (np. używając print_energy.m).']);
    end

    % Upewnienie się, że wektory 'dates' i 'y' są wektorami kolumnowymi
    dates = dates(:);
    y = y(:);
    
    % --- Walidacja danych i parametrów ---
    N = numel(y);
    
    degrees_for_rmse = (1:(N-1))'; % Kolumnowy wektor stopni

    % Znormalizowana dziedzina x \in [0,1] dla stabilności numerycznej
    x_normalized = linspace(0,1,N)';

    rmse_values = zeros(numel(degrees_for_rmse),1);

    fprintf('Rozpoczynanie obliczeń RMSE dla stopni od 1 do %d...\n', N-1);
    for idx = 1:numel(degrees_for_rmse)
        current_degree_m = degrees_for_rmse(idx);
        
        coeffs_m = polyfit_qr(x_normalized, y, current_degree_m);
        
        coeffs_m_for_polyval = coeffs_m(end:-1:1);
        
        y_approx_m = polyval(coeffs_m_for_polyval, x_normalized);
        
        sum_squared_errors = sum((y_approx_m - y).^2);
        mean_squared_error = sum_squared_errors / N;
        rmse_values(idx) = sqrt(mean_squared_error);
        
        if mod(current_degree_m, 25) == 0 || current_degree_m == numel(degrees_for_rmse)
            fprintf('Obliczono RMSE dla stopnia m = %d/%d. RMSE = %f\n', current_degree_m, N-1, rmse_values(idx));
        end
    end
    fprintf('Zakończono obliczenia RMSE.\n');

    coeffs_plot_temp = polyfit_qr(x_normalized, y, M);
    
    c = coeffs_plot_temp(end:-1:1); 
    
    ya = polyval(c, x_normalized);

    % --- Generowanie wykresów ---
    fig_handle = figure('Name', sprintf('Analiza RMSE i Aproksymacja dla %s - %s', country_name, source_name), ...
                        'NumberTitle', 'off');

    % Górny wykres: RMSE vs stopień wielomianu
    subplot(2,1,1);
    plot(degrees_for_rmse, rmse_values, 'b-o', 'MarkerFaceColor', 'b', 'MarkerSize', 3, 'LineWidth', 1);
    title('RMSE w zależności od stopnia wielomianu aproksymacyjnego');
    xlabel('Stopień wielomianu (m)');
    ylabel('RMSE (TWh)');
    grid on;
    if ~isempty(degrees_for_rmse)
      xlim([min(degrees_for_rmse), max(degrees_for_rmse)]);
    end

    % Dolny wykres: Dane oryginalne i aproksymacja wysokiego stopnia M
    subplot(2,1,2);
    plot(dates, y, 'k.', 'MarkerSize', 6, 'DisplayName', 'Dane oryginalne');
    hold on;
    plot(dates, ya, 'r-', 'LineWidth', 1.5, 'DisplayName', ['Aproksymacja (M=' num2str(M) ')']);
    hold off;
    
    title_str_bottom = sprintf('Produkcja energii (%s - %s) i aproksymacja (M=%d)', ...
                               strrep(country_name,'_',' '), strrep(source_name,'_',' '), M);
    title(title_str_bottom, 'Interpreter', 'none');
    xlabel('Data');
    ylabel('Produkcja energii (TWh)');
    legend('show', 'Location', 'best');
    grid on;
    
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
