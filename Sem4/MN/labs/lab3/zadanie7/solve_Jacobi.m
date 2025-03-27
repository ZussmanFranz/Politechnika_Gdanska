function [A,b,M,w,x,r_norm,iteration_count] = solve_Jacobi()
    % A - macierz z równania macierzowego A * x = b
    % b - wektor prawej strony równania macierzowego A * x = b
    % M - macierz pomocnicza opisana w instrukcji do Laboratorium 3
    %       – sprawdź wzór (5) w instrukcji, który definiuje M jako M_J.
    % w - wektor pomocniczy opisany w instrukcji do Laboratorium 3
    %       – sprawdź wzór (5) w instrukcji, który definiuje w jako w_J.
    % x - rozwiązanie równania macierzowego wyznaczone metodą Jacobiego
    % iteration_count - liczba iteracji wykonanych przy wyznaczeniu rozwiązania
    % r_norm - wektor norm residuum kolejnych przybliżeń rozwiązania:
    %       - r_norm(1) = norm(A*ones(N,1)-b)
    %       – r_norm(i) = norm(A*x-b), gdzie x stanowi i-te przybliżenie rozwiązania
    %       - length(r_norm) = iteration_count + 1
    
    N = randi([5000, 8000]);  

    [A,b] = generate_matrix(N);
    
    % Rozkład macierzy A na składowe
    D = diag(diag(A));      % Macierz diagonalna
    L = tril(A, -1);        % Macierz dolna (poniżej diagonali)
    U = triu(A, 1);         % Macierz górna (powyżej diagonali)
    
    iteration_count = 0;
    
    M = -D \ (L + U);
    w = D \ b;
    x = ones(N, 1);
    
    
    inorm = norm(A * x - b);
    r_norm = inorm;
    while(inorm>1e-12 && iteration_count<1000)
        x = M*x + w; % Aktualizacja rozwiązania
        inorm = norm(A * x - b);
        iteration_count = iteration_count + 1;
        r_norm = [ r_norm, inorm ];
    end
    
    % Wykres normy residuum w skali logarytmicznej
    figure;
    semilogy(0:iteration_count, r_norm, '-o', 'LineWidth', 2);
    xlabel('Liczba iteracji');
    ylabel('Norma residuum ||Ax - b||');
    title('Zbieżność metody Jacobiego');
    grid on;

    % Zapis wykresu do pliku
    print('zadanie3.png', '-dpng');
end