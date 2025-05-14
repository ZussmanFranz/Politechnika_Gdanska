function [dates, y, M, x_fine, c, ya, c_vpa, yv] = compare_double_vpa_approximations()
% W tej funkcji obliczenia wykonywane są na zmiennych vpa, jednakże spośród
% zwracanych zmiennych tylko c_vpa jest wektorem zmiennych vpa.
%
% Funkcja compare_double_vpa_approximations generuje trzy wykresy:
% 1) Górny wykres przedstawia aproksymację wyznaczoną na liczbach w podwójnej precyzji.
% 2) Środkowy wykres przedstawia aproksymację wyznaczoną na zmiennych vpa.
% 3) Dolny wykres przedstawia zakres wartości współczynników wielomianu
%    aproksymacyjnego wyznaczonych w precyzji double i vpa.
% 
% Dla kraju C oraz źródła energii S:
% dates - wektor energy_2025.C.S.Dates (daty pomiaru produkcji energii)
% y - wektor energy_2025.C.S.EnergyProduction (poziomy miesięcznych produkcji energii)
% M - stopień wielomianu aproksymacyjnego przedstawionego na wykresie
% x_fine - definiuje siatkę gęstą dla której obliczany jest wektor ya
%   Zachowaj jego definicję do oceny w Matlab Grader:
%   nodes = 4; % określa stopień zagęszczenia siatki gęstej
%   x_fine_vpa = linspace(vpa(0),vpa(1),(N-1)*nodes+1)';
%   x_fine = double(x_fine_vpa);
% c - współczynniki wielomianu aproksymacyjnego wyznaczone w obliczeniach
%   wykonywanych na zmiennych double. c = [c_M; ...; c_1; c_0]
% ya - wartości wielomianu aproksymacyjnego wyznaczone w punktach x_fine
%       z zastosowaniem zmiennych w podwójnej precyzji.
% c_vpa - współczynniki wielomianu aproksymacyjnego wyznaczone w obliczeniach
%       z zastosowaniem zmiennych vpa. c_vpa = [c_vpa_M; ...; c_vpa_0]
% yv - wartości wielomianu aproksymacyjnego wyznaczone w punktach x_fine_vpa
%       z zastosowaniem zmiennych vpa.

    digits(120); 

    % --- Wybór danych i parametrów ---
    M = 99;
    
    load ../energy_2025

    country_name = 'Poland'; 
    source_name = 'Coal';   

    if isfield(energy_2025, country_name) && isfield(energy_2025.(country_name), source_name)
        data_struct = energy_2025.(country_name).(source_name);
        if isfield(data_struct, 'Dates') && isfield(data_struct, 'EnergyProduction')
            dates = data_struct.Dates; 
            y = data_struct.EnergyProduction; 
        else
            error(['Brak wymaganych pól danych dla: ' country_name ', ' source_name]);
        end
    else
        error(['Nie znaleziono danych dla: ' country_name ', ' source_name]);
    end
    
    dates = dates(:);
    y = y(:);
    N = numel(y);
    

    % siatka rzadka (do wyznaczenia współczynników)
    x_vpa = linspace(vpa(0),vpa(1),N)';
    x = double(x_vpa);

    % siatka gęsta (do ewaluacji wielomianu)
    nodes = 4; 
    % Sprawdzenie N-1, aby uniknąć problemów z linspace gdy N=1 (choć N>=100 to wyklucza)
    if N > 1
        x_fine_vpa = linspace(vpa(0),vpa(1),(N-1)*nodes+1)';
    else % N=1, tylko jeden punkt
        x_fine_vpa = vpa(0); % lub vpa(x(1)) jeśli x jest znormalizowane inaczej
    end
    x_fine = double(x_fine_vpa);

    % --- Obliczenia dla wykresu górnego (precyzja double) ---
    c_double_temp = polyfit_qr(x, y, M);
    c = c_double_temp(end:-1:1);
    ya = polyval(c, x_fine);

    % --- Obliczenia dla wykresu środkowego (precyzja vpa) ---
    y_vpa_data = vpa(y);

    c_vpa_temp = polyfit_qr_vpa(x_vpa, y_vpa_data, M);
    c_vpa = c_vpa_temp(end:-1:1);
    yv_vpa = polyval_vpa(c_vpa, x_fine_vpa);
    yv = double(yv_vpa);

        % --- Generowanie wykresów ---
    fig_handle = figure('Name', sprintf('Porównanie aproksymacji Double vs VPA dla %s - %s, M=%d', country_name, source_name, M), ...
                        'NumberTitle', 'off');
    % Limity osi Y
    if ~isempty(y) && any(y) % Sprawdzenie czy y nie jest puste i czy zawiera jakieś niezerowe wartości
        valid_y = y(~isnan(y) & ~isinf(y)); % Usuń NaN/Inf z y przed obliczeniem max/min
        if isempty(valid_y)
            ymax_val = 1; ymin_val = -1; % Domyślne, jeśli y zawiera tylko NaN/Inf
        else
            max_abs_y = max(abs(valid_y));
            if max_abs_y == 0 % Jeśli wszystkie wartości to 0
                 ymax_val = 1; ymin_val = -1;
            else
                ymax_val = max(valid_y)*1.5; % Trochę więcej miejsca na górze
                ymin_val = min(valid_y)*1.5; % Trochę więcej miejsca na dole
                % Dostosowanie, jeśli max(y) jest 0 lub bliskie 0, a są wartości ujemne
                if max(valid_y) <= 0 && min(valid_y) < 0
                    ymax_val = 0.5 * abs(min(valid_y));
                end
                % Dostosowanie, jeśli min(y) jest 0 lub bliskie 0, a są wartości dodatnie
                if min(valid_y) >= 0 && max(valid_y) > 0
                     ymin_val = -0.5 * abs(max(valid_y));
                end
                % Standardowe limity z zadania, jeśli są sensowne
                if max(valid_y) > 0
                    ymax_task = max(valid_y)*2;
                    ymin_task = -0.25*ymax_task;
                    ymax_val = max(ymax_val, ymax_task); % Użyj większego zakresu
                    ymin_val = min(ymin_val, ymin_task);
                end

            end
        end
    else % Puste y lub same zera
        ymax_val = 1;
        ymin_val = -1;
    end
    
    % Zabezpieczenie przed NaN/Inf w limitach lub gdy ymin >= ymax
    if isnan(ymax_val) || isinf(ymax_val) || isnan(ymin_val) || isinf(ymin_val) || ymin_val >= ymax_val
        ymax_val = 1; ymin_val = -1;
    end


    % Wykres 1: Aproksymacja double
    subplot(3,1,1);
    plot(dates, y, 'k.', 'MarkerSize', 6, 'DisplayName', 'Dane oryginalne');
    hold on;
    plot(x_fine_to_dates(x_fine, dates), ya, 'b-', 'LineWidth', 1.5, 'DisplayName', ['Aproksymacja (double, M=' num2str(M) ')']);
    hold off;
    title('Aproksymacja wielomianowa (precyzja double)');
    xlabel('Data');
    ylabel('Produkcja energii (TWh)');
    legend('show', 'Location', 'best');
    grid on;
    % Zastosowanie ylim zamiast axis do ustawiania tylko limitów osi Y
    ylim([ymin_val, ymax_val]);


    % Wykres 2: Aproksymacja VPA
    subplot(3,1,2);
    plot(dates, y, 'k.', 'MarkerSize', 6, 'DisplayName', 'Dane oryginalne');
    hold on;
    plot(x_fine_to_dates(x_fine, dates), yv, 'r-', 'LineWidth', 1.5, 'DisplayName', ['Aproksymacja (VPA, M=' num2str(M) ')']);
    hold off;
    title('Aproksymacja wielomianowa (precyzja VPA)');
    xlabel('Data');
    ylabel('Produkcja energii (TWh)');
    legend('show', 'Location', 'best');
    grid on;
    % Zastosowanie ylim zamiast axis do ustawiania tylko limitów osi Y
    ylim([ymin_val, ymax_val]);

    % Wykres 3: Zakres współczynników
    subplot(3,1,3);
    plot_c_range(c_double_temp, c_vpa_temp); 

    saveas(fig_handle,'zadanie4.png');
end

function x_dates = x_fine_to_dates(x_fine_norm, original_dates)
    if isdatetime(original_dates(1))
        min_date_num = datenum(min(original_dates));
        max_date_num = datenum(max(original_dates));
        x_dates_num = min_date_num + x_fine_norm * (max_date_num - min_date_num);
        x_dates = datetime(x_dates_num, 'ConvertFrom', 'datenum');
    else % Jeśli dates są już numeryczne (np. lata, indeksy)
        min_val = min(original_dates);
        max_val = max(original_dates);
        x_dates = min_val + x_fine_norm * (max_val - min_val);
    end
end


function c = polyfit_qr(x, y, M_deg)
    x_col = x(:); 
    y_col = y(:); 
    N_pts = numel(x_col);

    if M_deg + 1 > N_pts
        error('polyfit_qr: Stopień M=%d jest za duży dla N_pts=%d. Wymagane M+1 <= N_pts.', M_deg, N_pts);
    end
    if M_deg < 0
        error('polyfit_qr: Stopień M=%d nie może być ujemny.', M_deg);
    end

    % Budowa macierzy Vandermonde A
    A = zeros(N_pts, M_deg+1); 
    for k_loop = 0:M_deg 
        A(:, k_loop+1) = x_col.^k_loop;
    end

    % Rozkład QR
    [Q1, R1] = qr(A, 0); % Economy size QR
    
    % Rozwiązanie R1 * c = Q1.' * y
    if rcond(R1) < eps(class(R1)) % Sprawdzenie uwarunkowania
         warning('polyfit_qr: Macierz R1 jest bliska osobliwej dla M=%d. Wyniki mogą być niedokładne.', M_deg);
    end
    c = R1 \ (Q1.' * y_col); % Zwraca [c0, c1, ..., cM]
end

function c_vpa_out = polyfit_qr_vpa(x_vpa_in, y_vpa_in, M_deg_vpa)
    x_col_vpa = x_vpa_in(:); 
    y_col_vpa = y_vpa_in(:); 
    N_pts_vpa = numel(x_col_vpa);

    if M_deg_vpa + 1 > N_pts_vpa
        error('polyfit_qr_vpa: Stopień M=%d jest za duży dla N_pts=%d. Wymagane M+1 <= N_pts.', M_deg_vpa, N_pts_vpa);
    end
     if M_deg_vpa < 0
        error('polyfit_qr_vpa: Stopień M=%d nie może być ujemny.', M_deg_vpa);
    end

    % TODO: Implementacja polyfit_qr_vpa (z poprzednich zadań)
    % Budowa macierzy Vandermonde A_vpa
    powers_vpa_vec = vpa(0:M_deg_vpa);
    A_vpa = x_col_vpa .^ powers_vpa_vec; 

    [Q_full_vpa, R_full_vpa] = qr(A_vpa);
    
    num_cols_A = M_deg_vpa + 1;
    Q1_vpa_econ = Q_full_vpa(:, 1:num_cols_A);
    R1_vpa_diag = R_full_vpa(1:num_cols_A, 1:num_cols_A);
    
    c_vpa_out = R1_vpa_diag \ (Q1_vpa_econ.' * y_col_vpa); % Zwraca [c0_vpa, ..., cM_vpa]
end

function y_val_vpa = polyval_vpa(coefficients_vpa_in, x_points_vpa_in)
    num_coeffs = length(coefficients_vpa_in);
    y_val_vpa = vpa(zeros(size(x_points_vpa_in)));  

    for i_coeff = 1:num_coeffs % coefficients_vpa_in jest [cM, ..., c0]
        y_val_vpa = y_val_vpa .* x_points_vpa_in + coefficients_vpa_in(i_coeff);
    end
end

function plot_c_range(c, c_vpa)
    c1log = sort(log10(abs(c)+1e-50)); % 1e-50: zabezpieczenie przez c(i)=0
    c2log = sort(log10(abs(c_vpa)+1e-50));

    plot(c1log,'kx-'); hold on
    plot(c2log,'bo-')
    hold off

    title('Zakres wartości współczynników c: double vs. vpa')
    xlabel('Indeks po sortowaniu według |c|')
    ylabel('$$\log_{10}\left(10^{-50} + |c|\right)$$', 'Interpreter', 'latex')

    legend('precyzja double', 'precyzja vpa', 'Location', 'eastoutside' );
end