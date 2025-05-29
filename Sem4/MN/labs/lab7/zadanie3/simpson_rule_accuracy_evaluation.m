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
    %   Tutaj "liczba podprzedziałów" jest interpretowana jako N_elementary (h-steps).
    %
    % integration_error – wektor zawierający błędy bezwzględne numerycznego
    %   wyznaczenia wartości całki oznaczonej.
    %
    % Nt – wektor wierszowy zawierający liczby "podprzedziałów całkowania" (paneli Simpsona, k).

    reference_value = 0.0473612919396179;

    ft_5 = failure_density_function(5);
    
    N_elementary_for_integral_1000 = 1000; 
    x_points_for_integral_1000 = linspace(0, 5, N_elementary_for_integral_1000 + 1);
    integral_1000 = simpson_rule(x_points_for_integral_1000);

    Nt = 5:50:10^4;
    num_evaluations = length(Nt);
    integration_error = zeros(1, num_evaluations); % Prealokacja wektora błędów

    integration_domain_a = 0;
    integration_domain_b = 5;

    for i = 1:num_evaluations
        k_panels_current = Nt(i); 
        
        N_elementary_current = 2 * k_panels_current; 
        
        % Generowanie węzłów dla N_elementary_current podprzedziałów h.
        current_x_points = linspace(integration_domain_a, integration_domain_b, N_elementary_current + 1);
        
        % Wywołanie funkcji simpson_rule, która oczekuje parzystej liczby elementarnych podprzedziałów.
        integral_approximation_current = simpson_rule(current_x_points);
        
        integration_error(i) = abs(integral_approximation_current - reference_value);
    end

    % Generowanie wykresu
    figure;
    loglog(Nt, integration_error, '-o');
    xlabel('Liczba paneli Simpsona (Nt)'); % Oś X to liczba paneli k
    ylabel('Błąd bezwzględny całkowania');
    title('Zależność błędu całkowania od liczby paneli (metoda Simpsona)');
    grid on;
    legend('Błąd metody Simpsona', 'Location', 'southwest');

    % Zapisanie wykresu do pliku
    saveas(gcf, 'zadanie3.png');
end

function integral_approximation = simpson_rule(x_domain_points)
    N_elementary_steps = length(x_domain_points) - 1; % Liczba elementarnych podprzedziałów 'N'

    if N_elementary_steps < 1 
        integral_approximation = 0;
        return;
    end

    if mod(N_elementary_steps, 2) ~= 0
        error('Metoda Simpsona (wzór 1/3) wymaga parzystej liczby elementarnych podprzedziałów (N).');
    end
    
    h = (x_domain_points(end) - x_domain_points(1)) / N_elementary_steps; 
    
    y_values = failure_density_function(x_domain_points);
    
    current_sum = y_values(1) + y_values(end);
    
    for j = 2:2:N_elementary_steps
        current_sum = current_sum + 4 * y_values(j);
    end
    
   
    if N_elementary_steps > 2
        for j = 3:2:(N_elementary_steps-1)
            current_sum = current_sum + 2 * y_values(j);
        end
    end
    
    integral_approximation = (h / 3) * current_sum;
end

function ft = failure_density_function(t)
    mu = 10;    % Średnia wartość
    sigma = 3;  % Odchylenie standardowe
    
    coefficient = 1 / (sigma * sqrt(2 * pi));
    exponent_numerator = -(t - mu).^2; 
    exponent_denominator = 2 * sigma^2;
    exponent = exponent_numerator / exponent_denominator; 
    
    ft = coefficient * exp(exponent);
end