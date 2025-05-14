function [dates, y, rmse_values, M, c_vpa, ya] = calculate_rmse_vpa()
% W tej funkcji obliczenia wykonywane są na zmiennych vpa, jednakże spośród
% zwracanych zmiennych tylko c_vpa jest wektorem zmiennych vpa.
%
% Funkcja calculate_rmse (VPA version, renamed for grader):
% 1) Wyznacza pierwiastek błędu średniokwadratowego w zależności od stopnia
%    aproksymacji wielomianowej danych przedstawiających produkcję energii.
% 2) Wyznacza i przedstawia na wykresie aproksymację wielomianową wysokiego
%    stopnia danych przedstawiających produkcję energii.
% Dla kraju C oraz źródła energii S:
% dates - wektor energy_2025.C.S.Dates (daty pomiaru produkcji energii)
% y - wektor energy_2025.C.S.EnergyProduction (poziomy miesięcznych produkcji energii)
% rmse_values(i,1) - RMSE wyznaczony dla wektora y i wielomianu stopnia degrees(i)
% M - stopień wielomianu aproksymacyjnego przedstawionego na wykresie
% c_vpa - współczynniki wielomianu aproksymacyjnego przedstawionego na wykresie:
%       c = [c_M; ...; c_1; c_0] (typu vpa)
% ya - wartości wielomianu aproksymacyjnego wyznaczone dla punktów danych
%       (typu double)

    digits(120); 

    M_plot = 99; 

    load energy_2025

    country_name = 'Poland'; 
    source_name = 'Coal';   

    if isfield(energy_2025, country_name) && isfield(energy_2025.(country_name), source_name)
        data_struct = energy_2025.(country_name).(source_name);
        if isfield(data_struct, 'Dates') && isfield(data_struct, 'EnergyProduction')
            dates = data_struct.Dates; 
            y = data_struct.EnergyProduction; 
        else
            error(['Data fields missing for: ' country_name ', ' source_name]);
        end
    else
        error(['Data not found for: ' country_name ', ' source_name]);
    end

    dates = dates(:);
    y = y(:); 
    
    N = numel(y); 
    
    % Define degrees for RMSE calculation
    degrees = 1:N-1; % For full report graph
    % degrees_candidate = [N-10, N-1];

    % Filter degrees to ensure they are valid (non-negative and feasible for N)
    % degrees = degrees_candidate(degrees_candidate >= 0 & (degrees_candidate + 1) <= N);
    if isempty(degrees) && N > 0 % If N is too small, e.g. N=5, N-10 is negative
        if N-1 >=0
            degrees = [N-1]; % Fallback to max possible degree (interpolation)
        else
             error('N is too small to define any polynomial degree.');
        end
    elseif isempty(degrees) && N == 0
        error('N is 0, no data to process.');
    end
    
    % Validate M_plot against N
    if M_plot + 1 > N
        error('Plotting degree M_plot=%d is too large for N=%d data points. M_plot+1 must be <= N.', M_plot, N);
    end
    if M_plot < 0
        error('Plotting degree M_plot=%d cannot be negative.', M_plot);
    end


    x_vpa = linspace(vpa(0),vpa(1),N)'; 
    y_vpa = vpa(y); 

    rmse_values = zeros(numel(degrees),1); 

    id = 1;
    for current_degree_m_vpa = degrees
        coeffs_m_vpa = polyfit_qr_vpa(x_vpa, y_vpa, current_degree_m_vpa);
        coeffs_m_for_polyval_vpa = coeffs_m_vpa(end:-1:1); 
        y_approx_m_vpa = polyval_vpa(coeffs_m_for_polyval_vpa, x_vpa); 
        
        N_vpa = vpa(N);
        sum_squared_errors_vpa = sum((y_approx_m_vpa - y_vpa).^2); 
        mean_squared_error_vpa = sum_squared_errors_vpa / N_vpa;   
        rmse_vpa = sqrt(mean_squared_error_vpa);                   
        
        rmse_values(id) = double(rmse_vpa); 
        id = id+1;
    end

    c_vpa_temp = polyfit_qr_vpa(x_vpa, y_vpa, M_plot); 
    c_vpa = c_vpa_temp(end:-1:1); 
    
    ya_vpa = polyval_vpa(c_vpa, x_vpa); 
    ya = double(ya_vpa); 
    
    M = M_plot; % Assign to output variable M

    % --- Generowanie wykresów ---
    fig_handle = figure('Name', sprintf('Analiza RMSE (VPA) i Aproksymacja dla %s - %s', country_name, source_name), ...
                        'NumberTitle', 'off');
    subplot(2,1,1);
    
    plot(degrees, rmse_values, 'm-s', 'MarkerFaceColor', 'm', 'MarkerSize', 5, 'LineWidth', 1.5);
    xlim_min = min(degrees);
    xlim_max = max(degrees);
    if xlim_min == xlim_max 
        xlim_min = max(0, xlim_min - 1); 
        xlim_max = xlim_max + 1;
    end
    xlim([xlim_min, xlim_max]);
   
    title('RMSE (obliczenia VPA) w zależności od stopnia wielomianu');
    xlabel('Stopień wielomianu (m)');
    ylabel('RMSE (TWh)');
    grid on;
    
    subplot(2,1,2);
    plot(dates, y, 'k.', 'MarkerSize', 6, 'DisplayName', 'Dane oryginalne (double)');
    hold on;
    plot(dates, ya, 'g-', 'LineWidth', 1.5, 'DisplayName', ['Aproksymacja (M=' num2str(M_plot) ', VPA)']);
    hold off;
    
    title_str_bottom = sprintf('Produkcja energii (%s - %s) i aproksymacja (M=%d, VPA)', ...
                               strrep(country_name,'_',' '), strrep(source_name,'_',' '), M_plot);
    title(title_str_bottom, 'Interpreter', 'none');
    xlabel('Data');
    ylabel('Produkcja energii (TWh)');
    legend('show', 'Location', 'best');
    grid on;

    saveas(fig_handle,'zadanie3.png') 
end

function y_val_vpa = polyval_vpa(coefficients_vpa, x_points_vpa)
    num_coeffs = length(coefficients_vpa);
    y_val_vpa = vpa(zeros(size(x_points_vpa)));  

    for i = 1:num_coeffs
        y_val_vpa = y_val_vpa .* x_points_vpa + coefficients_vpa(i);
    end
end

function c_coeffs_vpa = polyfit_qr_vpa(x_vpa_in, y_vpa_in, M_degree_vpa)
    x_col_vpa = x_vpa_in(:); 
    y_col_vpa = y_vpa_in(:); 
    
    N_pts_vpa = numel(x_col_vpa);

    if M_degree_vpa + 1 > N_pts_vpa
        error('polyfit_qr_vpa: Degree M=%d is too large for N_pts=%d. M+1 must be <= N_pts.', M_degree_vpa, N_pts_vpa);
    end
    if M_degree_vpa < 0
        error('polyfit_qr_vpa: Degree M=%d cannot be negative.', M_degree_vpa);
    end


    powers_vpa = vpa(0:M_degree_vpa);
    A_vpa = x_col_vpa .^ powers_vpa; 

    
    [Q_full_vpa, R_full_vpa] = qr(A_vpa);
    
    num_cols_A = M_degree_vpa + 1;
    Q1_vpa_econ = Q_full_vpa(:, 1:num_cols_A);
    R1_vpa = R_full_vpa(1:num_cols_A, 1:num_cols_A);

    
    c_coeffs_vpa = R1_vpa \ (Q1_vpa_econ.' * y_col_vpa);
end