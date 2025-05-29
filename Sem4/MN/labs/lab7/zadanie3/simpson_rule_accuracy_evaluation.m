function [ft_5, integral_1000, Nt, integration_error] = simpson_rule_accuracy_evaluation()
    % Funkcja służy do numerycznego obliczania całki oznaczonej metodą Simpsona
    % z funkcji gęstości prawdopodobieństwa awarii urządzenia elektronicznego.
    % Jej celem jest porównanie dokładności obliczeń
    % w zależności od liczby zastosowanych podprzedziałów całkowania.
    %
    % ft_5 – wartość funkcji gęstości prawdopodobieństwa obliczona dla t = 5.
    %
    % integral_1000 – przybliżona wartość całki oznaczonej na przedziale [0, 5]
    %   wyznaczona metodą Simpsona dla liczby podprzedziałów wynoszącej 1000.
    %
    % integration_error – wektor zawierający błędy bezwzględne numerycznego
    %   wyznaczenia wartości całki oznaczonej. Wartość integration_error(1,i)
    %   oznacza błąd obliczenia całki dla Nt(1,i) podprzedziałów:
    %   integration_error(1, i) = abs(integral_approximation - reference_value),
    %   gdzie reference_value to wzorcowa wartość całki.
    %
    % Nt – wektor wierszowy zawierający liczby podprzedziałów całkowania,
    %   dla których wyznaczane są przybliżenia całki i obliczany jest błąd.

    reference_value = 0.0473612919396179; % wartość referencyjna całki

    ft_5 = failure_density_function(5);
    
    N_for_integral_1000 = 1000; % liczba podprzedziałów całkowania (parzysta)
    x_points_for_integral_1000 = linspace(0, 5, N_for_integral_1000 + 1); % punkty dla N=1000
    integral_1000 = simpson_rule(x_points_for_integral_1000); % Wyznaczenie całki dla N=1000

    Nt = 5:50:10^4; % Wektor liczb podprzedziałów całkowania
    num_evaluations = length(Nt);
    integration_error = zeros(1, num_evaluations); % Prealokacja wektora błędów

    integration_domain_a = 0;
    integration_domain_b = 5;

    for i = 1:num_evaluations
        current_N_subintervals = Nt(i); % Aktualna liczba podprzedziałów
        current_x_points = linspace(integration_domain_a, integration_domain_b, current_N_subintervals + 1);
        
        integral_approximation_current = 0;

        if mod(current_N_subintervals, 2) == 0
            % Liczba podprzedziałów jest parzysta, można użyć metody Simpsona bezpośrednio
            integral_approximation_current = simpson_rule(current_x_points);
        else
            % Liczba podprzedziałów jest nieparzysta
            if current_N_subintervals == 1
                % Dla jednego podprzedziału użyj metody trapezów
                h_trapz = current_x_points(2) - current_x_points(1);
                y_trapz = failure_density_function(current_x_points);
                integral_approximation_current = (h_trapz / 2) * (y_trapz(1) + y_trapz(2));
            else
                x_simpson_part = current_x_points(1:current_N_subintervals); % Ma N_subintervals punktów -> N_subintervals-1 podprzedziałów
                integral_simpson_part = simpson_rule(x_simpson_part);
                
                % Punkty: current_x_points(N_subintervals) i current_x_points(N_subintervals+1)
                h_trapz_last = current_x_points(current_N_subintervals+1) - current_x_points(current_N_subintervals);
                y_trapz_last_pts = failure_density_function(current_x_points(current_N_subintervals : current_N_subintervals+1));
                integral_trapz_last_part = (h_trapz_last / 2) * (y_trapz_last_pts(1) + y_trapz_last_pts(2));
                
                integral_approximation_current = integral_simpson_part + integral_trapz_last_part;
            end
        end
        
        integration_error(i) = abs(integral_approximation_current - reference_value);
    end

    % Generowanie wykresu
    figure;
    loglog(Nt, integration_error, '-o');
    xlabel('Liczba podprzedziałów całkowania (Nt)');
    ylabel('Błąd bezwzględny całkowania');
    title('Zależność błędu całkowania od liczby podprzedziałów (metoda Simpsona)');
    grid on;
    legend('Błąd metody Simpsona', 'Location', 'southwest');

    % Zapisanie wykresu do pliku
    saveas(gcf, 'zadanie3.png');
end

function integral_approximation = simpson_rule(x)
    % Oblicza przybliżoną wartość całki oznaczonej z funkcji gęstości
    % prawdopodobieństwa (failure_density_function) przy użyciu
    % metody Simpsona.
    %
    % x – wektor rosnących wartości określających końce przedziałów całkowania.
    %     Dla n-elementowego wektora x zdefiniowanych jest n−1 przedziałów
    %     całkowania: [x(1), x(2)], [x(2), x(3)], ..., [x(n−1), x(n)].
    %
    % integral_approximation – przybliżona wartość całki oznaczonej

    k_subintervals = length(x) - 1;

    if k_subintervals < 1 % Jeśli brak przedziałów lub tylko 1 punkt
        integral_approximation = 0;
        return;
    end

    if mod(k_subintervals, 2) ~= 0
        error('Metoda Simpsona (wzór 1/3) wymaga parzystej liczby podprzedziałów.');
    end
    
    h = (x(end) - x(1)) / k_subintervals; % Szerokość podprzedziału
    
    y_values = failure_density_function(x); % Wartości funkcji w punktach x_i
    
    integral_sum = y_values(1) + y_values(end); % y_0 + y_k (gdzie k to k_subintervals)
    
    % Suma dla współczynników 4 (y_1, y_3, ..., y_{k-1})
    % Matlab indices: 2, 4, ..., k
    for j = 2:2:k_subintervals 
        integral_sum = integral_sum + 4 * y_values(j);
    end
    
    % Suma dla współczynników 2 (y_2, y_4, ..., y_{k-2})
    % Matlab indices: 3, 5, ..., k-1
    if k_subintervals > 2 % Tylko jeśli są wewnętrzne punkty z wagą 2
        for j = 3:2:k_subintervals-1
            integral_sum = integral_sum + 2 * y_values(j);
        end
    end
    
    integral_approximation = (h / 3) * integral_sum;
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
    
    ft = coefficient * exp(exponent);
end