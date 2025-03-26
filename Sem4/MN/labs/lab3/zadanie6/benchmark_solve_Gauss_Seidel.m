function [A,b,x,vec_loop_times,vec_iteration_count] = benchmark_solve_Gauss_Seidel(vN)
% Pomiar wydajności metody Gaussa-Seidla dla length(vN) równań macierzowych,
% przy czym liczba zmiennych i-tego równania wynosi vN(i).
% A - tablica komórkowa zawierająca zestaw macierzy A do równania macierzowego
%       A{i}*x{i}=b{i}, gdzie size(A{i},1) = vN(i)
% b - tablica komórkowa prawych stron równań A{i}*x{i}=b{i}
% x - tablica komórkowa z rozwiązaniami równań A{i}*x{i}=b{i}
% vec_loop_times(i) - czas wyznaczenia i-tego rozwiązania metodą Gaussa-Seidla
% vec_iterations_count(i) - liczba iteracji wykonana przy wyznaczeniu
%       i-tego rozwiązania metodą Gaussa-Seidla


vec_loop_times = zeros(1,length(vN));
vec_iteration_count = zeros(1,length(vN));

tol = 1e-12;   % Tolerancja normy residuum
max_iter = 1000; % Maksymalna liczba iteracji

for i=1:length(vN)
    N = vN(i);

    [A{i},b{i}] = generate_matrix(N);
    x{i} = ones(N,1);


    D = diag(diag(A{i})); % Macierz diagonalna
    L = tril(A{i}, -1);   % Macierz trójkątna dolna
    U = triu(A{i}, 1);    % Macierz trójkątna górna

    T = D + L;            % Macierz trójkątna dolna + diagonalna


    iteration_count = 0;
    inorm = 1e22;
    r_norm = [];
    tic

    while(inorm>tol && iteration_count<max_iter)
        x{i} = T \ (b{i} - U * x{i}); % Wzór iteracyjny Gaussa-Seidla
        inorm = norm(A{i} * x{i} - b{i}); 
        iteration_count = iteration_count + 1;
        r_norm = [r_norm, inorm];
    end

    vec_loop_times(i) = toc;
    vec_iteration_count(i) = iteration_count;
end

figure;

% Wykres górny - czas działania
subplot(2,1,1);
plot(vN, vec_loop_times, '-o', 'LineWidth', 2);
xlabel('Rozmiar macierzy N');
ylabel('Czas [s]');
title('Czas działania metody Gaussa-Seidla');
grid on;

% Wykres dolny - liczba iteracji
subplot(2,1,2);
plot(vN, vec_iteration_count, '-o', 'LineWidth', 2);
xlabel('Rozmiar macierzy N');
ylabel('Liczba iteracji');
title('Liczba iteracji metody Gaussa-Seidla');
grid on;

% Zapis wykresu
print('zadanie6.png', '-dpng');

end