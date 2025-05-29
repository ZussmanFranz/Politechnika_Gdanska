function [ft_5, integral_1000, Nt, integration_error] = midpoint_rule_accuracy_evaluation()
    % Funkcja służy do numerycznego obliczania całki oznaczonej metodą prostokątów
    % (wariant z punktem środkowym) z funkcji gęstości prawdopodobieństwa awarii
    % urządzenia elektronicznego. Jej celem jest porównanie dokładności obliczeń
    % w zależności od liczby zastosowanych podprzedziałów całkowania.
    %
    % ft_5 – wartość funkcji gęstości prawdopodobieństwa obliczona dla t = 5.
    %
    % integral_1000 – przybliżona wartość całki oznaczonej na przedziale [0, 5]
    %   wyznaczona metodą prostokątów dla liczby podprzedziałów wynoszącej 1000.
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

    ft_5 = failure_density_function(5);
    
    N_for_integral_1000 = 1000; % liczba podprzedziałów całkowania
    x_points_for_integral_1000 = linspace(0, 5, N_for_integral_1000 + 1); % punkty dla N=1000
    integral_1000 = midpoint_rule(x_points_for_integral_1000); % Wyznaczenie całki dla N=1000

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
        
        % Obliczenie przybliżonej wartości całki
        integral_approximation_current = midpoint_rule(current_x_points);
        
        % Obliczenie błędu bezwzględnego
        integration_error(i) = abs(integral_approximation_current - reference_value);
    end

    % Generowanie wykresu zależności błędu całkowania od liczby podprzedziałów
    figure; % Utworzenie nowego okna wykresu
    loglog(Nt, integration_error, '-o'); % Wykres w skali log-log z markerami
    xlabel('Liczba podprzedziałów całkowania (Nt)');
    ylabel('Błąd bezwzględny całkowania');
    title('Zależność błędu całkowania od liczby podprzedziałów');
    grid on; % Włączenie siatki
    legend('Błąd metody prostokątów (wariant środkowy)', 'Location', 'southwest');

    % Zapisanie wykresu do pliku
    saveas(gcf, 'zadanie1.png');

end


function integral_approximation = midpoint_rule(x)
    % Oblicza przybliżoną wartość całki oznaczonej z funkcji gęstości
    % prawdopodobieństwa (failure_density_function) przy użyciu
    % metody prostokątów (ang. midpoint rule).
    %
    % x – wektor rosnących wartości określających końce przedziałów całkowania.
    %     Dla n-elementowego wektora x zdefiniowanych jest n−1 przedziałów
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
    
    % Szerokość każdego podprzedziału (Delta_x), stała dla x wygenerowanego przez linspace
    delta_x = (b - a) / num_intervals;
    
    current_sum = 0;
    % Sumowanie wartości funkcji w środkach podprzedziałów
    % Pętla od i=1 do k (num_intervals)
    % i-ty podprzedział to [x(i), x(i+1)]
    for i = 1:num_intervals
        % Środek i-tego podprzedziału
        midpoint = (x(i) + x(i+1)) / 2;
        
        % Dodanie wartości funkcji w środku do sumy
        current_sum = current_sum + failure_density_function(midpoint);
    end
    
    % Przybliżona wartość całki (suma * Delta_x)
    integral_approximation = current_sum * delta_x;
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

    mu = 10;    % Średnia wartość (parametr μ)
    sigma = 3;  % Odchylenie standardowe (parametr σ)
    
    % Obliczenie wartości funkcji gęstości prawdopodobieństwa
    % Użycie operacji element-wise (np. .^, .*, ./, -) dla wektora t
    coefficient = 1 / (sigma * sqrt(2 * pi));
    exponent_numerator = -(t - mu).^2;
    exponent_denominator = 2 * sigma^2;
    exponent = exponent_numerator / exponent_denominator;
    
    ft = coefficient * exp(exponent); % exp() jest element-wise
end