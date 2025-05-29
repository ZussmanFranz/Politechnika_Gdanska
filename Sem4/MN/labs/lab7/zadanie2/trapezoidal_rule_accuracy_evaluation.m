function [ft_5, integral_1000, Nt, integration_error] = trapezoidal_rule_accuracy_evaluation()
    % Funkcja służy do numerycznego obliczania całki oznaczonej metodą trapezów
    % z funkcji gęstości prawdopodobieństwa awarii urządzenia elektronicznego.
    % Jej celem jest porównanie dokładności obliczeń
    % w zależności od liczby zastosowanych podprzedziałów całkowania.
    %
    % ft_5 – wartość funkcji gęstości prawdopodobieństwa obliczona dla t = 5.
    %
    % integral_1000 – przybliżona wartość całki oznaczonej na przedziale [0, 5]
    %   wyznaczona metodą trapezów dla liczby podprzedziałów wynoszącej 1000.
    %
    % integration_error – wektor zawierający błędy bezwzględne numerycznego
    %   wyznaczenia wartości całki oznaczonej. Wartość integration_error(1,i)
    %   oznacza błąd obliczenia całki dla Nt(1,i) podprzedziałów:
    %   integration_error(1, i) = abs(integral_approximation - reference_value),
    %   gdzie reference_value to wzorcowa wartość całki.
    %
    % Nt – wektor wierszowy zawierający liczby podprzedziałów całkowania,
    %   dla których wyznaczane są przybliżenia całki i obliczany jest błąd.

    reference_value = 0.0473612919396179; % wartość wzorcowa całki

    ft_5 = failure_density_function(5); % Obliczenie wartości funkcji dla t=5
    
    N_for_integral_1000 = 1000; % liczba podprzedziałów całkowania
    x_points_for_integral_1000 = linspace(0, 5, N_for_integral_1000 + 1); % punkty dla N=1000
    integral_1000 = trapezoidal_rule(x_points_for_integral_1000); % Wyznaczenie całki dla N=1000

    Nt = 5:50:10^4; % Wektor liczb podprzedziałów całkowania
    num_evaluations = length(Nt);
    integration_error = zeros(1, num_evaluations); % Prealokacja wektora błędów

    % Definicja przedziału całkowania [a, b]
    integration_domain_a = 0;
    integration_domain_b = 5;

    % Pętla do obliczania całki i błędu dla różnych liczb podprzedziałów
    for i = 1:num_evaluations
        current_N_subintervals = Nt(i); % Aktualna liczba podprzedziałów
        
        % Punkty dla aktualnej liczby podprzedziałów
        current_x_points = linspace(integration_domain_a, integration_domain_b, current_N_subintervals + 1);
        
        % Obliczenie przybliżonej wartości całki metodą trapezów
        integral_approximation_current = trapezoidal_rule(current_x_points);
        
        % Obliczenie błędu bezwzględnego
        integration_error(i) = abs(integral_approximation_current - reference_value);
    end

    % Generowanie wykresu zależności błędu całkowania od liczby podprzedziałów
    figure; % Utworzenie nowego okna wykresu
    loglog(Nt, integration_error, '-o'); % Wykres w skali log-log z markerami
    xlabel('Liczba podprzedziałów całkowania (Nt)');
    ylabel('Błąd bezwzględny całkowania');
    title('Zależność błędu całkowania od liczby podprzedziałów (metoda trapezów)');
    grid on; % Włączenie siatki
    legend('Błąd metody trapezów', 'Location', 'southwest');

    % Zapisanie wykresu do pliku
    saveas(gcf, 'zadanie2.png');

end


function integral_approximation = trapezoidal_rule(x)
    % Oblicza przybliżoną wartość całki oznaczonej z funkcji gęstości
    % prawdopodobieństwa (failure_density_function) przy użyciu
    % metody trapezów.
    %
    % x – wektor rosnących wartości określających końce podprzedziałów całkowania.
    %     Dla n-elementowego wektora x zdefiniowanych jest n−1 podprzedziałów
    %     całkowania: [x(1), x(2)], [x(2), x(3)], ..., [x(n−1), x(n)].
    %
    % integral_approximation – przybliżona wartość całki oznaczonej

    num_intervals = length(x) - 1; % Liczba podprzedziałów (k)
    
    if num_intervals < 1
        integral_approximation = 0; % Jeśli brak przedziałów, całka = 0
        return;
    end
    
    a = x(1); % Początek przedziału całkowania
    b = x(end); % Koniec przedziału całkowania
    
    % Szerokość każdego podprzedziału (Δx), stała dla x wygenerowanego przez linspace
    delta_x = (b - a) / num_intervals;
    
    % Wartości funkcji f(x_i) na wszystkich punktach siatki
    fx_values = failure_density_function(x);
    
    % Złożona reguła trapezów:
    current_sum = fx_values(1) + fx_values(end); % f(x_0) + f(x_k)
    
    if num_intervals > 1 % Jeśli istnieją punkty wewnętrzne x_1, ..., x_{k-1}
        % Suma wartości funkcji w punktach wewnętrznych (x(2) do x(end-1))
        current_sum = current_sum + 2 * sum(fx_values(2:end-1));
    end
    
    integral_approximation = (delta_x / 2) * current_sum;
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
    
    % Obliczenie wartości funkcji gęstości prawdopodobieństwa
    % Użycie operacji element-wise (np. .^, .*, ./, -) dla wektora t
    coefficient = 1 / (sigma * sqrt(2 * pi));
    exponent_numerator = -(t - mu).^2;
    exponent_denominator = 2 * sigma^2;
    exponent = exponent_numerator / exponent_denominator; % Dzielenie przez skalar, lub element-wise jeśli t jest wektorem
    
    ft = coefficient * exp(exponent); % Funkcja exp() działa element-wise
end