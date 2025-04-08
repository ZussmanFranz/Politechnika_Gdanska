function [xvec,xdif,xsolution,ysolution,iterations] = velocity_bisection()
    % Wyznacza miejsce zerowe funkcji velocity_difference metodą bisekcji.
    % xvec - wektor z kolejnymi przybliżeniami miejsca zerowego, gdzie xvec(1)= (a+b)/2
    % xdif - wektor różnic kolejnych przybliżeń miejsca zerowego
    %   xdif(i) = abs(xvec(i+1)-xvec(i));
    % xsolution - obliczone miejsce zerowe
    % ysolution - wartość funkcji velocity_difference wyznaczona dla t=xsolution
    % iterations - liczba iteracji wykonana w celu wyznaczenia xsolution

    a = 1; % lewa granica przedziału poszukiwań miejsca zerowego
    b = 40; % prawa granica przedziału poszukiwań miejsca zerowego
    ytolerance = 1e-12; % tolerancja wartości funkcji w przybliżonym miejscu zerowym.
    % Warunek abs(f1(xsolution))<ytolerance określa jak blisko zera ma znaleźć
    % się wartość funkcji w obliczonym miejscu zerowym funkcji f1(), aby obliczenia
    % zostały zakończone.
    max_iterations = 1000; % maksymalna liczba iteracji wykonana przez alg. bisekcji

    fa = velocity_difference(a);
    % fb = velocity_difference(b);

    xvec = zeros(max_iterations, 1); % Preallocate xvec for efficiency
    xdif = zeros(max_iterations - 1, 1); % Preallocate xdif for efficiency

    xsolution = Inf;
    ysolution = Inf;
    iterations = max_iterations;

    for ii=1:max_iterations
        c = (a + b) / 2; % Środek przedziału
        xvec(ii) = c; % Zapisanie przybliżenia w prealokowanym wektorze
        fc = velocity_difference(c); % Obliczenie wartości funkcji w punkcie c

        if abs(fc) < ytolerance
            xsolution = c;
            ysolution = fc;
            iterations = ii;
            xvec = xvec(1:ii); % Przycięcie wektora do rzeczywistego rozmiaru
            xdif = xdif(1:ii-1); % Przycięcie wektora różnic
            break;
        end

        if fa * fc < 0
            b = c;
        else
            a = c;
            fa = fc;
        end

        if ii > 1
            xdif(ii - 1) = abs(xvec(ii) - xvec(ii - 1));
        end
    end

    % Rysowanie wykresów
    figure;
    subplot(2, 1, 1);
    plot(1:length(xvec), xvec, '-o');
    title('Kolejne przybliżenia miejsca zerowego');
    xlabel('Iteracje');
    ylabel('Przybliżenie');

    subplot(2, 1, 2);
    semilogy(1:length(xdif), xdif, '-o');
    title('Różnica między kolejnymi przybliżeniami');
    xlabel('Iteracje');
    ylabel('Różnica (logarytmiczna)');

end

function velocity_delta = velocity_difference (t)
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