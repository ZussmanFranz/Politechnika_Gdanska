function [xvec,xdif,xsolution,ysolution,iterations] = impedance_bisection()
    % Wyznacza miejsce zerowe funkcji impedance_difference metodą bisekcji.
    % xvec - wektor z kolejnymi przybliżeniami miejsca zerowego, gdzie xvec(1)= (a+b)/2
    % xdif - wektor różnic kolejnych przybliżeń miejsca zerowego
    %   xdif(i) = abs(xvec(i+1)-xvec(i));
    % xsolution - obliczone miejsce zerowe
    % ysolution - wartość funkcji impedance_difference wyznaczona dla f=xsolution
    % iterations - liczba iteracji wykonana w celu wyznaczenia xsolution

    a = 1; % lewa granica przedziału poszukiwań miejsca zerowego
    b = 10; % prawa granica przedziału poszukiwań miejsca zerowego
    ytolerance = 1e-12; % tolerancja wartości funkcji w przybliżonym miejscu zerowym.
    % Warunek abs(f1(xsolution))<ytolerance określa jak blisko zera ma znaleźć
    % się wartość funkcji w obliczonym miejscu zerowym funkcji f1(), aby obliczenia
    % zostały zakończone.
    max_iterations = 1000; % maksymalna liczba iteracji wykonana przez alg. bisekcji

    fa = impedance_difference(a);
    fb = impedance_difference(b);

    xvec = [];
    xdif = [];
    iterations = 0;

    if fa * fb > 0
        error('Brak zmiany znaku funkcji w przedziale [%f, %f]', a, b);
    end

    % Pętla bisekcji
    while iterations < max_iterations
        % Licznik iteracji
        iterations = iterations + 1;
        
        c = (a + b) / 2;
        fc = impedance_difference(c);

        xvec(end+1, 1) = c;     

        % Wybór nowego przedziału
        if fa * fc < 0
            b = c;
            fb = fc;
        else
            a = c;
            fa = fc;
        end

        % Oblicz różnice między kolejnymi przybliżeniami
        if length(xvec) > 1
            xdif(end+1, 1) = abs(xvec(end) - xvec(end-1));
        end

        % Sprawdzenie warunku zakończenia
        if abs(fc) < ytolerance
            break;
        end  
    end

    % Wyniki
    xsolution = xvec(end);
    ysolution = impedance_difference(xsolution);

    % Wykresy
    figure;

    subplot(2,1,1);
    plot(1:length(xvec), xvec, '-o');
    title('Przybliżenia miejsca zerowego');
    xlabel('Numer iteracji');
    ylabel('Częstotliwość [Hz]');
    grid on;

    subplot(2,1,2);
    semilogy(1:length(xdif), xdif, '-o');
    title('Różnice między kolejnymi przybliżeniami (logarytmicznie)');
    xlabel('Numer iteracji');
    ylabel('|x_{n+1} - x_n|');
    grid on;

    saveas(gcf, 'zadanie2.png');

end

function impedance_delta = impedance_difference (f)
    % Tutaj wklej definicję funkcji zdefiniowanej w zadaniu 1.

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