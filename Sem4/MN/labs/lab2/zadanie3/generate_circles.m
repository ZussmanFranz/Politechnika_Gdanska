function [circles, a, b, r_max] = generate_circles(n_max)
    % GENERATE_CIRCLES losuje n_max okręgów wpisanych w prostokąt
    
    % wejście:
    %   n_max - liczba okręgów do wylosowania
    
    % wyjście:
    %   circles - macierz [n x 3], gdzie każdy wiersz to [X, Y, R] określający środek i promień okręgu
    %   a, b  - wymiary prostokąta (wierzchołki: (0,0), (a,0), (a,b), (0,b))
    %   r_max - maksymalny promień okręgu (losowany z przedziału [20,50])
    
    % Losowanie wymiarów prostokąta
    a = 150 + (250 - 150)*rand; % a ∈ [150, 250]
    b = 50 + (100 - 50)*rand;   % b ∈ [50, 100]
    
    % Losowanie maksymalnego promienia
    r_max = 20 + (50 - 20)*rand; % r_max ∈ [20, 50]
    
    circles = zeros(n_max, 3); % inicjalizacja macierzy wynikowej
    count = 0;                % licznik zaakceptowanych okręgów
    
    while count < n_max
        
        % Losowanie promienia z zakresu (0, r_max]
        R = r_max * rand;
        if R == 0
            continue; % pomijamy przypadek zerowego promienia
        end
        
        % Losowanie środka okręgu, aby okrąg mieścił się całkowicie w prostokącie
        X = R + (a - 2*R)*rand; % X ∈ [R, a - R]
        Y = R + (b - 2*R)*rand; % Y ∈ [R, b - R]
        
        % Sprawdzamy, czy nowy okrąg nie przecina żadnego już zaakceptowanego
        valid = true;
        for i = 1:count
            X_prev = circles(i, 1);
            Y_prev = circles(i, 2);
            R_prev = circles(i, 3);
            d = sqrt((X - X_prev)^2 + (Y - Y_prev)^2);
            if d < (R + R_prev)
                valid = false;
                break;
            end
        end
        
        if valid
            count = count + 1;
            circles(count, :) = [X, Y, R];
        end
    end
end
    