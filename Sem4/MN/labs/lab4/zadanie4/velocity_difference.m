function velocity_delta = velocity_difference(t)
    % Wyznacza prędkość rakiety po czasie t od startu pomniejszoną o wartość M.
    % t - [s] czas od startu rakiety
    % velocity_delta [m/s]

    % Parametry
    g = 1.622;      % [m/s^2] przyspieszenie grawitacyjne na Księżycu
    m0 = 150000;    % [kg] masa początkowa rakiety
    q = 2700;       % [kg/s] tempo zużycia paliwa
    u = 2000;       % [m/s] prędkość gazów wylotowych
    M = 700;        % [m/s] wartość odniesienia

    % Sprawdzenie poprawności t
    if t >= m0 / q
        error('Błąd: czas t przekracza czas, w którym masa rakiety osiąga zero.');
    elseif t <= 0
        error('Czas ma być dodatni');
    end

    % Obliczenie prędkości zgodnie ze wzorem (3)
    v = u * log(m0 / (m0 - q * t)) - g * t;

    % Różnica względem wartości odniesienia (wzór 4)
    velocity_delta = v - M;

end