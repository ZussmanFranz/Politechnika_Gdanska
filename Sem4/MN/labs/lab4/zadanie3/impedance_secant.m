function [xvec,xdif,xsolution,ysolution,iterations] = impedance_secant()
    % Wyznacza miejsce zerowe funkcji impedance_difference metodą siecznych.
    % xvec - kolejne przybliżenia miejsca zerowego, xvec(1) = x2
    % xdif - różnice kolejnych przybliżeń
    % xsolution - wynik końcowy
    % ysolution - wartość funkcji dla xsolution
    % iterations - liczba wykonanych iteracji

    x0 = 1;
    x1 = 10;
    ytolerance = 1e-12;
    max_iterations = 1000;

    f0 = impedance_difference(x0);
    f1 = impedance_difference(x1);

    xvec = [];
    xdif = [];
    iterations = 0;

    for i = 1:max_iterations
        iterations = i;

        % Sprawdzenie czy nie dzielimy przez zero
        if abs(f1 - f0) < eps
            warning('Dzielnik zbyt mały, zatrzymuję iterację.');
            break;
        end

        % Obliczenie nowego przybliżenia metodą siecznych
        x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
        f2 = impedance_difference(x2);

        xvec(end+1,1) = x2;

        if length(xvec) > 1
            xdif(end+1,1) = abs(xvec(end) - xvec(end-1));
        end

        % Sprawdzenie kryterium dokładności
        if abs(f2) < ytolerance
            break;
        end

        % Przygotowanie do następnej iteracji
        x0 = x1;
        f0 = f1;
        x1 = x2;
        f1 = f2;
    end

    xsolution = xvec(end);
    ysolution = impedance_difference(xsolution);

    % Wykresy
    figure;

    subplot(2,1,1);
    plot(1:length(xvec), xvec, '-o');
    title('Przybliżenia miejsca zerowego (metoda siecznych)');
    xlabel('Numer iteracji');
    ylabel('Częstotliwość [Hz]');
    grid on;

    subplot(2,1,2);
    semilogy(1:length(xdif), xdif, '-o');
    title('Różnice między kolejnymi przybliżeniami (log)');
    xlabel('Numer iteracji');
    ylabel('|x_{n+1} - x_n|');
    grid on;

    saveas(gcf, 'zadanie3.png');
end

function impedance_delta = impedance_difference(f)
    % Parametry obwodu
    R = 525;                 
    C = 7e-5;                
    L = 3;                   
    M = 75;                  

    if f <= 0
        error('Częstotliwość musi być większa od zera.');
    end

    % Obliczenie modułu impedancji
    term1 = 1 / R^2;
    term2 = (2 * pi * f * C - 1 / (2 * pi * f * L))^2;
    Z_mod = 1 / sqrt(term1 + term2);

    impedance_delta = Z_mod - M;
end
