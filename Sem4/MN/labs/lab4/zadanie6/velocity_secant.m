function [xvec,xdif,xsolution,ysolution,iterations] = velocity_secant()
    % Wyznacza miejsce zerowe funkcji velocity_difference metodą siecznych.
    % xvec - wektor z kolejnymi przybliżeniami miejsca zerowego;
    %   xvec(1)=x2 przy założeniu, że x0 i x1 są punktami startowymi
    % xdif - wektor różnic kolejnych przybliżeń miejsca zerowego
    %   xdif(i) = abs(xvec(i+1)-xvec(i));
    % xsolution - obliczone miejsce zerowe
    % ysolution - wartość funkcji velocity_difference wyznaczona dla f=xsolution
    % iterations - liczba iteracji wykonana w celu wyznaczenia xsolution

    x0 = 1; % pierwszy punkt startowy metody siecznych
    x1 = 40; % drugi punkt startowy metody siecznych
    ytolerance = 1e-12;% tolerancja wartości funkcji w przybliżonym miejscu zerowym.
    % Warunek abs(f1(xsolution))<ytolerance określa jak blisko zera ma znaleźć
    % się wartość funkcji w obliczonym miejscu zerowym funkcji f1(), aby obliczenia
    % zostały zakończone.
    max_iterations = 1000; % maksymalna liczba iteracji wykonana przez alg. bisekcji

    f0 = velocity_difference(x0);
    f1 = velocity_difference(x1);

    xvec = []; % Initialize xvec as an empty array for dynamic resizing
    xdif = []; % Initialize xdif as an empty array for dynamic resizing
    xsolution = Inf;
    ysolution = Inf;
    iterations = max_iterations;

    for ii = 1:max_iterations
        % Obliczenie kolejnego przybliżenia x2 metodą siecznych
        x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
        xvec(ii) = x2; % Zapisanie przybliżenia
        f2 = velocity_difference(x2); % Obliczenie wartości funkcji w x2

        % Sprawdzenie warunku zakończenia
        if abs(f2) < ytolerance
            xsolution = x2;
            ysolution = f2;
            iterations = ii;
            break;
        end

        % Aktualizacja punktów startowych
        x0 = x1;
        f0 = f1;
        x1 = x2;
        f1 = f2;

        % Obliczenie różnicy między kolejnymi przybliżeniami
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