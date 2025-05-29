function [ft_5, yrmax, Nt, xr, yr, integration_error] = monte_carlo_accuracy_evaluation()
    % Numeryczne całkowanie metodą Monte Carlo.
    %
    % ft_5 - gęstość funkcji prawdopodobieństwa dla n=5
    %
    % yrmax - maksymalna dopuszczalna wartość współrzędnej y losowanych punktów
    %
    % Nt - wektor wierszowy zawierający liczby losowań, dla których obliczano
    %     wektor błędów całkowania integration_error.
    %
    % [xr, yr] - tablice komórkowe zawierające informacje o wylosowanych punktach.
    %     Tablice te mają rozmiar [1, length(Nt)]. W komórkach xr{1,i} oraz yr{1,i}
    %     zawarte są współrzędne x oraz y wszystkich punktów zastosowanych
    %     do obliczenia całki przy losowaniu Nt(1,i) punktów.
    %
    % integration_error - wektor wierszowy. Każdy element integration_error(1,i)
    %     zawiera błąd całkowania obliczony dla liczby losowań równej Nt(1,i).
    %     Zakładając, że obliczona wartość całki dla Nt(1,i) próbek wynosi
    %     integration_result, błąd jest definiowany jako:
    %     integration_error(1,i) = abs(integration_result - reference_value),
    %     gdzie reference_value to wartość referencyjna całki.

    reference_value = 0.0473612919396179; % wartość referencyjna całki

    ft_5 = failure_density_function(5);

    % Parametry dla metody Monte Carlo:
    % Przedział całkowania [integration_domain_a, integration_domain_b]
    integration_domain_a = 0; 
    integration_domain_b = 5;

    determined_yrmax = ft_5; 

    % Wektor liczby losowanych punktów
    Nt_vector = 5:50:10^4;
    num_evaluations = length(Nt_vector);
    
    % Inicjalizacja tablic wyjściowych
    xr_cell_array = cell(1, num_evaluations);
    yr_cell_array = cell(1, num_evaluations);
    integration_error_vector = zeros(1, num_evaluations);

    % Pętla obliczająca całkę i błąd dla różnej liczby losowanych punktów
    for i = 1:num_evaluations
        current_N_samples = Nt_vector(i);
        
        [integral_result, current_xr_coords, current_yr_coords] = ...
            monte_carlo_integral(current_N_samples, integration_domain_b, determined_yrmax);
            
        % Zapisanie wylosowanych współrzędnych do tablic komórkowych
        xr_cell_array{1,i} = current_xr_coords;
        yr_cell_array{1,i} = current_yr_coords;
        
        % Obliczenie błędu bezwzględnego
        integration_error_vector(i) = abs(integral_result - reference_value);
    end

    % Generowanie wykresu
    figure;
    loglog(Nt_vector, integration_error_vector, '-o');
    xlabel('Liczba losowanych punktów (Nt)');
    ylabel('Błąd bezwzględny całkowania');
    title('Zależność błędu całkowania od liczby losowań (Metoda Monte Carlo)');
    grid on;
    legend('Błąd metody Monte Carlo', 'Location', 'northeast');

    % Zapisanie wykresu do pliku
    saveas(gcf, 'zadanie4.png');

    % Przypisanie wartości do zmiennych wyjściowych zgodnie z sygnaturą funkcji
    % (zgodnie ze zmiennymi w linii `function [...] = monte_carlo_accuracy_evaluation()`)
    yrmax = determined_yrmax; 
    Nt = Nt_vector;
    xr = xr_cell_array;
    yr = yr_cell_array;
    integration_error = integration_error_vector;
end

function [integral_approximation, x_coords, y_coords] = monte_carlo_integral(N, xmax, ymax_bound)
    % Oblicza przybliżoną wartość całki oznaczonej z funkcji gęstości
    % prawdopodobieństwa (failure_density_function) przy użyciu
    % metody Monte Carlo.
    %
    % N – liczba losowanych punktów
    % xmax – koniec przedziału całkowania [0, xmax]
    % ymax – górna granica wartości funkcji w przedziale [0, xmax]
    %        (musi spełniać warunek ymax ≥ max(f(x)))
    % integral_approximation – przybliżona wartość całki
    % x – wektor wierszowy o długości N z wylosowanymi wartościami x z [0, xmax]
    % y – wektor wierszowy o długości N z wylosowanymi wartościami y z [0, ymax]

    x_coords = xmax * rand(1, N);
    y_coords = ymax_bound * rand(1, N);

    fx_values_at_x_coords = failure_density_function(x_coords);

    points_under_curve = (y_coords <= fx_values_at_x_coords);
    N1 = sum(points_under_curve);

 
    S_rectangle_area = xmax * ymax_bound;
    integral_approximation = (N1 / N) * S_rectangle_area;
end

function ft = failure_density_function(t)
    % Zwraca wartości funkcji gęstości prawdopodobieństwa wystąpienia awarii
    % urządzenia elektronicznego dla zadanych wartości czasu t.
    %
    % t – wektor wartości czasu (wyrażonych w latach), dla których obliczane
    %   są wartości funkcji gęstości prawdopodobieństwa.
    %
    % ft – wektor zawierający wartości funkcji gęstości prawdopodobieństwa
    %      odpowiadające kolejnym elementom wektora t.

    mu = 10;    % Średnia wartość
    sigma = 3;  % Odchylenie standardowe
    
    coefficient = 1 / (sigma * sqrt(2 * pi));
    exponent_numerator = -(t - mu).^2; 
    exponent_denominator = 2 * sigma^2;
    exponent = exponent_numerator / exponent_denominator; 
    
    ft = coefficient * exp(exponent); % funkcja exp() działa element-wise
end