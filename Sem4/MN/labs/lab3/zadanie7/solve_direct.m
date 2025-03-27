function [x,r_norm] = solve_direct(A, b)
    % A, b - macierz i wektor z równania macierzowego A * x = b
    % L - macierz trójkątna dolna pochodząca z wywołania [L,U,P] = lu(A);
    % U - macierz trójkątna górna
    % P - macierz permutacji
    % y - wektor pomocniczy y=L\(P*b)
    % x - wektor rozwiązania
    % r_norm - norma residuum: norm(A*x-b)
    % t_factorization - czas faktoryzacji macierzy A (czas działania funkcji lu)
    % t_substitution - czas wyznaczenia rozwiązań równań z macierzami trójkątnymi L i U
    % t_direct - czas wyznaczenia rozwiąznia równania macierzowego metodą LU


    % Pomiar czasu faktoryzacji LU
    tic;
    % [L, U, P] = lu(A);
    t_factorization = toc;

    % Pomiar czasu podstawień w przód i wstecz
    tic;
    % y = L \ (P * b); % Forward substitution
    % x = U \ y;       % Back substitution
    x = A \ b;
    t_substitution = toc;

    % Całkowity czas rozwiązania
    t_direct = t_factorization + t_substitution;

    % Obliczenie normy residuum
    r_norm = norm(A * x - b);

    % Wykres czasu obliczeń
    % figure;
    % r = [t_direct, t_factorization, t_substitution];
    % bar(r);
    % xlabel('Etap obliczeń');
    % ylabel('Czas (s)');
    % title('Czas obliczeń metodą LU');
    % set(gca, 'XTickLabel', {'Całkowity', 'Faktoryzacja', 'Podstawienia'});

    % % Zapis wykresu do pliku
    % print('direct.png', '-dpng');

end