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
% M - stopień wielomianu aproksymacyjnego przedstawionego na wykresie
% c_vpa - współczynniki wielomianu aproksymacyjnego przedstawionego na wykresie:
%       c = [c_M; ...; c_1; c_0] (typu vpa)
% ya - wartości wielomianu aproksymacyjnego wyznaczone dla punktów danych
%       (typu double)

    digits(120); 

    M = 99; 

    load energy_2025

    country_name = 'Poland'; 
    source_name = 'Coal';   
    % country_name = 'EU'; source_name = 'Total';

    data_struct = energy_2025.(country_name).(source_name);
    dates = data_struct.Dates; 
    y = data_struct.EnergyProduction; 

    dates = dates(:);
    y = y(:); 
    
    N = numel(y); 
    
    degrees = [N-10, N-1];

    x_vpa = linspace(vpa(0),vpa(1),N)'; 
    y_vpa = vpa(y); 

    rmse_values = zeros(numel(degrees),1); 

    % fprintf('Rozpoczynanie obliczeń RMSE (VPA) dla wybranych stopni...\n');
    id = 1;
    for current_degree_m_vpa = degrees
        % fprintf('Obliczanie RMSE dla stopnia M = %d (VPA)...\n', current_degree_m_vpa);
        
        coeffs_m_vpa = polyfit_qr_vpa(x_vpa, y_vpa, current_degree_m_vpa);
        coeffs_m_for_polyval_vpa = coeffs_m_vpa(end:-1:1); 
        y_approx_m_vpa = polyval_vpa(coeffs_m_for_polyval_vpa, x_vpa); 
        
        N_vpa = vpa(N);
        sum_squared_errors_vpa = sum((y_approx_m_vpa - y_vpa).^2); 
        mean_squared_error_vpa = sum_squared_errors_vpa / N_vpa;   
        rmse_vpa = sqrt(mean_squared_error_vpa);                   
        
        rmse_values(id) = double(rmse_vpa); 
        % fprintf('Stopień M = %d, RMSE (VPA) = %e\n', current_degree_m_vpa, rmse_values(id));
        id = id+1;
    end
    % fprintf('Zakończono obliczenia RMSE (VPA).\n');

    % fprintf('Obliczanie aproksymacji dla M = %d (VPA) na potrzeby wykresu...\n', M);
    c_vpa_temp = polyfit_qr_vpa(x_vpa, y_vpa, M); 
    c_vpa = c_vpa_temp(end:-1:1); 
    
    ya_vpa = polyval_vpa(c_vpa, x_vpa); 
    ya = double(ya_vpa); 

    fig_handle = figure('Name', sprintf('Analiza RMSE (VPA) i Aproksymacja dla %s - %s', country_name, source_name), ...
                        'NumberTitle', 'off');

    subplot(2,1,1);
    plot(degrees, rmse_values, 'm-s', 'MarkerFaceColor', 'm', 'MarkerSize', 5, 'LineWidth', 1.5);
    title('RMSE (obliczenia VPA) w zależności od stopnia wielomianu');
    xlabel('Stopień wielomianu (m)');
    ylabel('RMSE (TWh)');
    grid on;
    if ~isempty(degrees)
      xlim_min = min(degrees);
      xlim_max = max(degrees);
      if xlim_min == xlim_max 
          xlim_min = xlim_min - 1;
          xlim_max = xlim_max + 1;
          if xlim_min < 0 && xlim_max > 0 % Avoid xlim_min being negative if original degree was 0 or 1
              xlim_min = 0;
          elseif xlim_min < 0
              xlim_min = 0; xlim_max = 2; % Default for single small degree
          end
      end
      xlim([xlim_min, xlim_max]);
    end

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
        % This check is important for polyfit to be well-defined
        error('polyfit_qr_vpa: Degree M=%d is too large for N_pts=%d data points. M+1 must be <= N_pts.', M_degree_vpa, N_pts_vpa);
    end

    A_vpa = vpa(zeros(N_pts_vpa, M_degree_vpa+1)); 
    for k_vpa = 0:M_degree_vpa 
        A_vpa(:, k_vpa+1) = x_col_vpa.^k_vpa;
    end

    try
        % For sym objects (which vpa creates), qr(A) returns full Q and R.
        [Q_full_vpa, R_full_vpa] = qr(A_vpa);
        
        % Extract the parts corresponding to an economy QR decomposition
        num_cols_A = M_degree_vpa + 1;
        Q1_vpa_econ = Q_full_vpa(:, 1:num_cols_A);
        R1_vpa = R_full_vpa(1:num_cols_A, 1:num_cols_A);

    catch ME_qr_vpa
        % Fallback if qr fails for some reason with VPA matrices
        c_coeffs_vpa = A_vpa \ y_col_vpa;
        return;
    end
    
    c_coeffs_vpa = R1_vpa \ (Q1_vpa_econ.' * y_col_vpa);
end