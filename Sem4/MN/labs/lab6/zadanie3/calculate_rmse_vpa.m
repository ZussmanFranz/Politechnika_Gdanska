function [dates, y, rmse_values, M, c_vpa, ya] = calculate_rmse_vpa()
% W tej funkcji obliczenia wykonywane są na zmiennych vpa, jednakże spośród
% zwracanych zmiennych tylko c_vpa jest wektorem zmiennych vpa.
%
% Funkcja calculate_rmse_vpa:
% 1) Wyznacza pierwiastek błędu średniokwadratowego w zależności od stopnia
%    aproksymacji wielomianowej danych przedstawiających produkcję energii.
% 2) Wyznacza i przedstawia na wykresie aproksymację wielomianową wysokiego
%    stopnia danych przedstawiających produkcję energii.
% Dla kraju C oraz źródła energii S:
% dates - wektor energy_2025.C.S.Dates (daty pomiaru produkcji energii)
% y - wektor energy_2025.C.S.EnergyProduction (poziomy miesięcznych produkcji energii)
% rmse_values(i,1) - RMSE wyznaczony dla wektora y i wielomianu stopnia degrees(i)
%     Rozmiar kolumnowego wektora wynosi length(y)-1.
% M - stopień wielomianu aproksymacyjnego przedstawionego na wykresie
% c_vpa - współczynniki wielomianu aproksymacyjnego przedstawionego na wykresie:
%       c = [c_M; ...; c_1; c_0] (typu vpa)
% ya - wartości wielomianu aproksymacyjnego wyznaczone dla punktów danych
%       (rozmiar wektora ya powinien być taki sam jak rozmiar wektora y) (typu double)

    digits(120); % określa liczbę cyfr dziesiętnych w zmiennych vpa

    % --- Parametry ---
    M = 99; 

    % --- Wczytanie danych ---
    load ../energy_2025

    country_name = 'Poland'; 
    source_name = 'Coal';   
    % country_name = 'EU'; source_name = 'Total';

    % Odczyt danych z wybranej struktury
    if isfield(energy_2025, country_name) && isfield(energy_2025.(country_name), source_name)
        data_struct = energy_2025.(country_name).(source_name);
        if isfield(data_struct, 'Dates') && isfield(data_struct, 'EnergyProduction')
            dates = data_struct.Dates; % dates pozostaje typu double/datetime
            y = data_struct.EnergyProduction; % y początkowo jest typu double
        else
            error(['Wybrana struktura danych dla kraju: ' country_name ' i źródła: ' source_name ...
                   ' nie zawiera wymaganych pól ''Dates'' lub ''EnergyProduction''.']);
        end
    else
        error(['Wybrane dane dla kraju: ' country_name ' i źródła: ' source_name ...
               ' nie istnieją w pliku energy_2025.mat. Sprawdź dostępne opcje.']);
    end

    % Upewnienie się, że wektory 'dates' i 'y' są wektorami kolumnowymi
    dates = dates(:);
    y = y(:); % y jest typu double
    
    % --- Walidacja danych i parametrów ---
    N = numel(y); % Liczba punktów danych
    

    degrees = [N-10, N-1];

    % Konwersja danych wejściowych do vpa
    x_vpa = linspace(vpa(0),vpa(1),N)'; % Znormalizowana dziedzina [0,1] jako vpa
    y_vpa = vpa(y); % Wektor y jako vpa

    rmse_values = zeros(numel(degrees),1); % Wynikowy RMSE będzie typu double

    fprintf('Rozpoczynanie obliczeń RMSE (VPA) dla wybranych stopni...\n');
    % Oblicz RMSE dla każdego stopnia w 'degrees'
    id = 1;
    for current_degree_m_vpa = degrees
        fprintf('Obliczanie RMSE dla stopnia M = %d (VPA)...\n', current_degree_m_vpa);
        
        % Wyznaczenie współczynników wielomianu stopnia current_degree_m_vpa (vpa)
        coeffs_m_vpa = polyfit_qr_vpa(x_vpa, y_vpa, current_degree_m_vpa);
        
        % Odwrócenie kolejności współczynników dla funkcji polyval_vpa
        coeffs_m_for_polyval_vpa = coeffs_m_vpa(end:-1:1); % vpa
        
        % Wyznaczenie wartości wielomianu aproksymacyjnego (vpa)
        y_approx_m_vpa = polyval_vpa(coeffs_m_for_polyval_vpa, x_vpa); % vpa
        
        N_vpa = vpa(N);
        sum_squared_errors_vpa = sum((y_approx_m_vpa - y_vpa).^2); % vpa
        mean_squared_error_vpa = sum_squared_errors_vpa / N_vpa;   % vpa
        rmse_vpa = sqrt(mean_squared_error_vpa);                   % vpa
        
        rmse_values(id) = double(rmse_vpa); % Konwersja wyniku RMSE do double
        fprintf('Stopień M = %d, RMSE (VPA) = %e\n', current_degree_m_vpa, rmse_values(id));
        id = id+1;
    end
    fprintf('Zakończono obliczenia RMSE (VPA).\n');

    % Aproksymacja wielomianu wysokiego stopnia M (dla dolnego wykresu) z VPA
    fprintf('Obliczanie aproksymacji dla M = %d (VPA) na potrzeby wykresu...\n', M);
    % polyfit_qr_vpa zwraca [c0_vpa; c1_vpa; ...; cM_vpa]
    c_vpa_temp = polyfit_qr_vpa(x_vpa, y_vpa, M); % vpa
    
    % Odwrócenie kolejności współczynników dla polyval_vpa i dla wyjściowego c_vpa
    % c_vpa = [cM_vpa; ...; c1_vpa; c0_vpa] (typ vpa)
    c_vpa = c_vpa_temp(end:-1:1); 
    
    % Wyznaczenie wartości wielomianu aproksymacyjnego dla stopnia M (vpa)
    ya_vpa = polyval_vpa(c_vpa, x_vpa); % vpa
    ya = double(ya_vpa); % Konwersja do double na potrzeby wykresu i zwracanej wartości


    % --- Generowanie wykresów ---
    fig_handle = figure('Name', sprintf('Analiza RMSE (VPA) i Aproksymacja dla %s - %s', country_name, source_name), ...
                        'NumberTitle', 'off');

    % Górny wykres: RMSE vs stopień wielomianu (VPA)
    subplot(2,1,1);
    plot(degrees, rmse_values, 'm-s', 'MarkerFaceColor', 'm', 'MarkerSize', 5, 'LineWidth', 1.5);
    title('RMSE (obliczenia VPA) w zależności od stopnia wielomianu');
    xlabel('Stopień wielomianu (m)');
    ylabel('RMSE (TWh)');
    grid on;
    if ~isempty(degrees)
      xlim_min = min(degrees);
      xlim_max = max(degrees);
      if xlim_min == xlim_max % handle case with single degree
          xlim_min = xlim_min - 1;
          xlim_max = xlim_max + 1;
      end
      xlim([xlim_min, xlim_max]);
    end

    % Dolny wykres: Dane oryginalne i aproksymacja wysokiego stopnia M (z VPA)
    subplot(2,1,2);
    plot(dates, y, 'k.', 'MarkerSize', 6, 'DisplayName', 'Dane oryginalne (double)');
    hold on;
    plot(dates, ya, 'g-', 'LineWidth', 1.5, 'DisplayName', ['Aproksymacja (M=' num2str(M) ', VPA)']);
    hold off;
    
    title_str_bottom = sprintf('Produkcja energii (%s - %s) i aproksymacja (M=%d, VPA)', ...
                               strrep(country_name,'_',' '), strrep(source_name,'_',' '), M);
    title(title_str_bottom, 'Interpreter', 'none');
    xlabel('Data');
    ylabel('Produkcja energii (TWh)');
    legend('show', 'Location', 'best');
    grid on;

    saveas(gcf,'zadanie3.png') 
end

% --- Lokalna funkcja polyval_vpa ---
function y_val_vpa = polyval_vpa(coefficients_vpa, x_points_vpa)
    num_coeffs = length(coefficients_vpa);
    y_val_vpa = vpa(zeros(size(x_points_vpa)));  

    for i = 1:num_coeffs
        y_val_vpa = y_val_vpa .* x_points_vpa + coefficients_vpa(i);
    end
end

% --- Lokalna funkcja polyfit_qr_vpa ---
function c_coeffs_vpa = polyfit_qr_vpa(x_vpa_in, y_vpa_in, M_degree_vpa)
    x_col_vpa = x_vpa_in(:); 
    y_col_vpa = y_vpa_in(:); 
    
    N_pts_vpa = numel(x_col_vpa);

    A_vpa = vpa(zeros(N_pts_vpa, M_degree_vpa+1)); 
    for k_vpa = 0:M_degree_vpa 
        A_vpa(:, k_vpa+1) = x_col_vpa.^k_vpa;
    end

    c_coeffs_vpa = R1_vpa \ (Q1_vpa_econ.' * y_col_vpa); % vpa
end