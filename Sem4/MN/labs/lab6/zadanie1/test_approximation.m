function [dates, y, M, c, ya] = test_approximation()
% Wyznacza aproksymację wielomianową danych przedstawiających produkcję energii.
% Dla kraju C oraz źródła energii S:
% dates - wektor energy_2025.C.S.Dates (daty pomiaru produkcji energii)
% y - wektor energy_2025.C.S.EnergyProduction (poziomy miesięcznych produkcji energii)
% M - stopień wielomianu aproksymacyjnego
% c - współczynniki wielomianu aproksymacyjnego: c = [c_M; ...; c_1; c_0]
% ya - wartości wielomianu aproksymacyjnego wyznaczone dla punktów danych
%       (rozmiar wektora ya powinien być taki sam jak rozmiar wektora y)

    load energy_2025

    country = 'Poland';
    source = 'Coal';
    
    % Sprawdzenie, czy wybrane dane istnieją w strukturze
    if isfield(energy_2025, country) && isfield(energy_2025.(country), source)
        data_struct = energy_2025.(country).(source);
        % Sprawdzenie, czy istnieją wymagane pola 'Dates' i 'EnergyProduction'
        if isfield(data_struct, 'Dates') && isfield(data_struct, 'EnergyProduction')
            dates = data_struct.Dates;
            y = data_struct.EnergyProduction;
        else
            error(['Wybrana struktura danych dla kraju: ' country ' i źródła: ' source ...
                   ' nie zawiera wymaganych pól ''Dates'' lub ''EnergyProduction''.']);
        end
    else
        error(['Wybrane dane dla kraju: ' country ' i źródła: ' source ...
               ' nie istnieją w pliku energy_2025.mat. Sprawdź dostępne opcje (np. używając print_energy.m).']);
    end

    % Upewnienie się, że wektory 'dates' i 'y' są wektorami kolumnowymi
    dates = dates(:);
    y = y(:);
    
    % --- Walidacja danych i parametrów ---
    N_data_points = numel(y); % Liczba punktów danych
    
    % Wymaganie: co najmniej 100 elementów danych
    if N_data_points < 100
        error_msg_N = sprintf(['Wybrany zbiór danych (%s, %s) zawiera %d elementów. ' ...
                               'Wymagane jest co najmniej 100 elementów. Proszę wybrać inny zbiór danych.'], ...
                               country, source, N_data_points);
        error(error_msg_N);
    end
    
    % Jeśli zbiór danych jest pusty (choć powyższy warunek powinien to wyłapać)
    if N_data_points == 0
         error(['Wybrany zbiór danych (%s, %s) jest pusty. Proszę wybrać inny.'], country, source);
    end
    
    M = 12; % Stopień wielomianu aproksymacyjnego, M \in [1,12]
    
    % Sprawdzenie poprawności stopnia wielomianu M
    if M < 1 || M > 12
        error('Stopień wielomianu M musi być w przedziale [1,12].');
    end
    

    % --- Aproksymacja wielomianowa ---
    N = N_data_points; % liczba danych (zgodnie z oryginalnym kodem szkieletowym)
    % Znormalizowana dziedzina x \in [0,1] dla stabilności numerycznej obliczeń
    x_normalized = linspace(0,1,N)'; 

    c_polyfit = polyfit_qr(x_normalized, y, M); 

    c = c_polyfit(end:-1:1); 

    ya = polyval(c, x_normalized); 

    % --- Generowanie wykresu ---
    figure;
    plot(dates, y, 'o', 'MarkerSize', 5, 'DisplayName', 'Dane oryginalne');
    hold on;
    plot(dates, ya, '-', 'LineWidth', 2, 'DisplayName', ['Aproksymacja wielomianowa (M=' num2str(M) ')']);
    hold off;
    
    % Tytuł i etykiety osi (uwzględnienie polskich znaków i formatowania)
    title_str = sprintf('Produkcja energii w %s ze źródła %s', strrep(country,'_',' '), strrep(source,'_',' '));
    title(title_str, 'Interpreter', 'none'); % 'none' interpreter for underscore if not using strrep
    xlabel('Data');
    ylabel('Produkcja energii (TWh)');
    legend('show', 'Location', 'best');
    grid on;    

    saveas(gcf,'zadanie1.png')
end

function c = polyfit_qr(x, y, M)
    x_col = x(:); % Upewnienie się, że x jest wektorem kolumnowym
    y_col = y(:); % Upewnienie się, że y jest wektorem kolumnowym
    
    N_pts = numel(x_col); % Liczba punktów danych

    A = zeros(N_pts, M+1); % Prealokacja macierzy
    for k = 0:M % k jest potęgą x, od 0 do M
        A(:, k+1) = x_col.^k;
    end
    

    [Q1, R1] = qr(A, 0); 
    
    c = R1 \ (Q1.' * y_col);
end