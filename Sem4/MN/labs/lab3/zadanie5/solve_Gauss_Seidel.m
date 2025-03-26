function [A,b,U,T,w,x,r_norm,iteration_count] = solve_Gauss_Seidel()
    % A - macierz z równania macierzowego A * x = b
    % b - wektor prawej strony równania macierzowego A * x = b
    % U - macierz trójkątna górna, która zawiera wszystkie elementy macierzy A powyżej głównej diagonalnej,
    % T - macierz trójkątna dolna równa A-U
    % w - wektor pomocniczy opisany w instrukcji do Laboratorium 3
    %       – sprawdź wzór (7) w instrukcji, który definiuje w jako w_{GS}.
    % x - rozwiązanie równania macierzowego
    % r_norm - wektor norm residuum kolejnych przybliżeń rozwiązania; norm(A*x-b);
    % iteration_count - liczba iteracji wymagana do wyznaczenia rozwiązania
    %       metodą Gaussa-Seidla
    
    N = randi([5000, 9000]);
    tol = 1e-12; % Tolerancja dla normy residuum
    max_iter = 1000; % Maksymalna liczba iteracji

    [A,b] = generate_matrix(N);
    
    % Podział macierzy A na składowe
    D = diag(diag(A)); % Macierz diagonalna
    L = tril(A, -1);   % Macierz trójkątna dolna
    U = triu(A, 1);    % Macierz trójkątna górna
    
    T = D + L;         % Macierz trójkątna dolna + diagonalna

    w = T \ b;

    x = ones(N, 1); % Początkowe przybliżenie rozwiązania
    
    res = norm(A * x - b); % Norma residuum
    r_norm = res;    % Przechowywanie norm residuum

    iteration_count = 0;
    while(res > tol && iteration_count < max_iter)
        x = T \ (b - U * x); % Wzór iteracyjny Gaussa-Seidla
        res = norm(A * x - b); 
        iteration_count = iteration_count + 1;
        r_norm = [r_norm, res];
    end
    
    % Wykres normy residuum w skali logarytmicznej
    figure;
    semilogy(0:iteration_count, r_norm, '-o', 'LineWidth', 2);
    xlabel('Liczba iteracji');
    ylabel('Norma residuum ||Ax - b||');
    title('Zbieżność metody Gaussa Seidla');
    grid on;

    % Zapis wykresu do pliku
    print('zadanie5.png', '-dpng');

end