function [dates, y, M, a, b, x_fine, ya, rmse_values] = test_trigonometric_approximation()
% 1) Wyznacza pierwiastek błędu średniokwadratowego w zależności od liczby
%    harmonicznych zastosowanych w aproksymacji trygonometrycznej.
% 2) Wyznacza i przedstawia na wykresie aproksymację trygonometryczną.
% Dla kraju C oraz źródła energii S:
% dates - wektor energy_2025.C.S.Dates (daty pomiaru produkcji energii)
% y - wektor energy_2025.C.S.EnergyProduction (poziomy miesięcznych produkcji energii)
% M - liczba harmonicznych zastosowana w aproksymacji (dla wykresu)
% a - współczynniki amplitudowe funkcji cosinus
% b - współczynniki amplitudowe funkcji sinus
% x_fine - określa próbkowanie funkcji aproksymacyjnej.
% ya - wartości aproksymacji trygonometrycznej wyznaczone dla siatki punktów
%       określonej przez x_fine
% rmse_values(i,1) - RMSE wyznaczony dla wektora y i rezultatu aproksymacji
%       trygonometrycznej.

    M = 20; 

    load ../energy_2025

    % --- Wybór danych ---
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

    if N < 100
        error('Wybrany zbiór danych ma %d elementów. Wymagane jest co najmniej 100.', N);
    end
    if M < 1 || M > floor(N/2)
        warning('Liczba harmonicznych M=%d jest poza zalecanym zakresem [1, floor(N/2)=%d]. Może to prowadzić do nieoczekiwanych wyników.', M, floor(N/2));
    end


    x = (0:N-1)';  
    k_max = floor(N/2);

    Mx = 4; 
    if N > 1
        x_fine = linspace(0,N-1,Mx*(N-1)+1)';
    else % N=1
        x_fine = 0;
    end
    
    [a, b] = calculate_ab_from_DFT(y);
    
    ya = trigonometric_approximation(x_fine, N, M, a, b);

    rmse_values = zeros(k_max,1);
    if k_max > 0 % Oblicz RMSE tylko jeśli są jakiekolwiek harmoniczne
        for k_rmse = 1:k_max
            ya4rmse = trigonometric_approximation(x, N, k_rmse, a, b);
            rmse_values(k_rmse) = sqrt(mean((y - ya4rmse).^2));
        end
    end

    % --- Wykresy ---
    fig_handle = figure('Name', sprintf('Aproksymacja trygonometryczna dla %s - %s', country_name, source_name), ...
                        'NumberTitle', 'off');

    % Górny wykres: RMSE
    subplot(2,1,1);
    if k_max > 0
        plot(1:k_max, rmse_values, 'b-o', 'MarkerFaceColor', 'b', 'MarkerSize', 3);
        xlim([1, k_max]); % Ustawienie limitów osi X
    else
        plot([],[]); % Pusty wykres, jeśli k_max = 0
        text(0.5,0.5,'Brak harmonicznych do analizy RMSE (N jest zbyt małe)','HorizontalAlignment','center');
        xlim([0 1]); ylim([0 1]);
    end
    title('RMSE w zależności od liczby harmonicznych');
    xlabel('Liczba harmonicznych (k)');
    ylabel('RMSE (TWh)');
    grid on;

    % Dolny wykres: Aproksymacja
    subplot(2,1,2);
    plot(dates, y, 'k.', 'MarkerSize', 6, 'DisplayName', 'Dane oryginalne');
    hold on;
    
    % Przekształcenie x_fine do skali dat dla wykresu
    if N > 1
        if isdatetime(dates(1))
            min_date_num = datenum(min(dates));
            max_date_num = datenum(max(dates));
            dates_fine_num = min_date_num + (x_fine / (N-1)) * (max_date_num - min_date_num);
            dates_fine = datetime(dates_fine_num, 'ConvertFrom', 'datenum');
        else 
            min_date_val = min(dates);
            max_date_val = max(dates);
            dates_fine = min_date_val + (x_fine / (N-1)) * (max_date_val - min_date_val);
        end
    else 
        dates_fine = dates(1); 
    end

    plot(dates_fine, ya, 'r-', 'LineWidth', 1.5, 'DisplayName', ['Aproksymacja (M=' num2str(M) ' harmonicznych)']);
    hold off;
    title(['Aproksymacja trygonometryczna (M=' num2str(M) ' harmonicznych)']);
    xlabel('Data');
    ylabel('Produkcja energii (TWh)');
    legend('show', 'Location', 'best');
    grid on;
    
    saveas(fig_handle,'zadanie5.png');
end

function ya = trigonometric_approximation(x_eval, N_data, M_harmonics, a_coeffs, b_coeffs)
    if(N_data==0)
        ya = [];
        return;
    end

    k_max_coeffs = length(a_coeffs) - 1; 
    ya = zeros(length(x_eval), 1);

    ya = ya + a_coeffs(1);  

    num_harmonics_to_use = min(M_harmonics, k_max_coeffs);

    for n_harmonic = 1:num_harmonics_to_use
        ya = ya + a_coeffs(n_harmonic+1) * cos(2*pi*n_harmonic*x_eval/N_data) + ...
                   b_coeffs(n_harmonic+1) * sin(2*pi*n_harmonic*x_eval/N_data);
    end
end


function [a, b] = calculate_ab_from_DFT(x_signal)
    if(isempty(x_signal)) 
        a = [];
        b = [];
        return
    end
    N_samples = length(x_signal);
    Y_fft = fft(x_signal);
    k_max_harmonics = floor(N_samples/2); 

    a = zeros(k_max_harmonics+1, 1); 
    b = zeros(k_max_harmonics+1, 1); 

    a(1) = real(Y_fft(1)) / N_samples;

    for n_idx = 1:k_max_harmonics 
        fft_component_idx = n_idx + 1; 
        is_nyquist_freq = (mod(N_samples,2) == 0) && (n_idx == N_samples/2);
        coeff_idx = n_idx + 1; 

        if is_nyquist_freq
            a(coeff_idx) = real(Y_fft(fft_component_idx)) / N_samples;
            b(coeff_idx) = 0; 
        else
            a(coeff_idx) = 2 * real(Y_fft(fft_component_idx)) / N_samples;
            b(coeff_idx) = -2 * imag(Y_fft(fft_component_idx)) / N_samples;
        end
    end
end