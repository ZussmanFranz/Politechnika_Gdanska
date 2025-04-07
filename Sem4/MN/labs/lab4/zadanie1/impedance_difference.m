function impedance_delta = impedance_difference(f)
% Wyznacza moduł impedancji równoległego obwodu rezonansowego RLC pomniejszoną o wartość M.
% f - częstotliwość [Hz]

    % Parametry obwodu
    R = 525;                 % Rezystancja [Ohm]
    C = 7e-5;                % Pojemność [F]
    L = 3;                   % Indukcyjność [H]
    M = 75;                  % Wartość odniesienia modułu impedancji

    % Sprawdzenie poprawności częstotliwości
    if f <= 0
        error('Częstotliwość musi być większa od zera.');
    end

    % Obliczenie modułu impedancji zgodnie ze wzorem (1)
    term1 = 1 / R^2;
    term2 = (2 * pi * f * C - 1 / (2 * pi * f * L))^2;
    Z_mod = 1 / sqrt(term1 + term2);

    % Różnica względem wartości odniesienia
    impedance_delta = Z_mod - M;

end
    