function [node_counts, exact_runge, exact_sine, V, interpolated_runge, interpolated_sine] =...
    plot_runge_sine_interpolations()
% Generuje dwa wykresy przedstawiające interpolacje funkcji Rungego oraz
% funkcji sinusoidalnej. Funkcja zwraca:
% 1) trzy wektory wierszowe
% 2) trzy tablice komórkowe (cell arrays) o rozmiarze [1,4].

    % Lista liczby węzłów interpolacyjnych do przetestowania
    node_counts = [3, 5, 9, 13];

    % Definicja funkcji Rungego i sinusoidalnej
    runge_function = @(x) 1 ./ (1 + 25 * x.^2);
    sine_function = @(x) sin(2 * pi * x);

    % Gęsta siatka punktów do testowania interpolacji
    x_fine = linspace(-1, 1, 1000);

    % Wartości wzorcowe funkcji
    exact_runge = runge_function(x_fine);
    exact_sine = sine_function(x_fine);

    % Przygotowanie miejsca na wyniki
    V = cell(1, length(node_counts));
    interpolated_runge = cell(1, length(node_counts));
    interpolated_sine = cell(1, length(node_counts));

    % Rysowanie funkcji wzorcowych
    subplot(2,1,1);
    plot(x_fine, exact_runge, 'k--', 'LineWidth', 2, 'DisplayName', 'Wartości wzorcowe');
    hold on;
    subplot(2,1,2);
    plot(x_fine, exact_sine, 'k--', 'LineWidth', 2, 'DisplayName', 'Wartości wzorcowe');
    hold on;

    for i = 1:length(node_counts)
        N = node_counts(i);
        x_nodes = linspace(-1, 1, N)';

        V{i} = get_vandermonde_matrix(x_nodes);

        % Funkcja Rungego
        y_runge = runge_function(x_nodes);
        coefficients_runge = V{i} \ y_runge;
        coefficients_runge = coefficients_runge(end:-1:1);
        interpolated_runge{i} = polyval(coefficients_runge, x_fine);

        % Funkcja sinusoidalna
        y_sine = sine_function(x_nodes);
        coefficients_sine = V{i} \ y_sine;
        coefficients_sine = coefficients_sine(end:-1:1);
        interpolated_sine{i} = polyval(coefficients_sine, x_fine);

        % Rysowanie
        subplot(2,1,1);
        plot(x_fine, interpolated_runge{i}, 'DisplayName', sprintf('%d węzłów', N));
        subplot(2,1,2);
        plot(x_fine, interpolated_sine{i}, 'DisplayName', sprintf('%d węzłów', N));
    end

    subplot(2,1,1);
    title('Interpolacja funkcji Rungego');
    xlabel('x'); ylabel('f(x)');
    legend show; legend('Location', 'eastoutside'); grid on;

    subplot(2,1,2);
    title('Interpolacja funkcji sinusoidalnej');
    xlabel('x'); ylabel('f(x)');
    legend show; legend('Location', 'eastoutside'); grid on;

    % Zapis do pliku
    set(gcf, 'Position', [100, 100, 1200, 800]);
    saveas(gcf, 'zadanie1.png');
end

function V = get_vandermonde_matrix(x)
    % Buduje macierz Vandermonde’a na podstawie wektora węzłów interpolacji x.
    N = length(x);
    V = zeros(N);
    for i = 1:N
        V(i, :) = x(i).^(0:N-1);
    end
end
