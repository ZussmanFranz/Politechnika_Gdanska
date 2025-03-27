% wczytanie macierzy A oraz wektora b z pliku poprzez wywołanie polecenia load filtr_dielektryczny.mat

% wyznaczenie rozwiązania równania macierzowego trzema badanymi metodami poprzez wywołania
% solve_direct, solve_Jacobi, solve_Gauss_Seidel

% wypisanie wartości trzech norm residuów wyznaczonych dla rozwiązań obliczonych trzema metodami

% Wczytanie macierzy A oraz wektora b z pliku filtr_dielektryczny.mat
load('filtr_dielektryczny.mat'); 


% Wyznaczenie rozwiązania trzema metodami
[x_direct, residuum_norm_direct] = solve_direct(A, b);
[x_Jacobi, residuum_norm_Jacobi] = solve_Jacobi(A, b);
[x_Gauss_Seidel, residuum_norm_Gauss_Seidel] = solve_Gauss_Seidel(A, b);

% Zapis wyników do pliku filter_solutions.m
fileID = fopen('filter_solutions.m', 'w');
fprintf(fileID, 'function [residuum_norm_direct, residuum_norm_Jacobi, residuum_norm_Gauss_Seidel] = filter_solutions()\n');
fprintf(fileID, '%%   residuum_norm_direct - norma residuum dla rozwiązania metodą bezpośrednią\n');
fprintf(fileID, '%%   residuum_norm_Jacobi - norma residuum dla rozwiązania metodą Jacobiego\n');
fprintf(fileID, '%%   residuum_norm_Gauss_Seidel - norma residuum dla rozwiązania metodą Gaussa-Seidelea\n\n');
fprintf(fileID, '    residuum_norm_direct = %e;\n', residuum_norm_direct(end));
fprintf(fileID, '    residuum_norm_Jacobi = %e;\n', residuum_norm_Jacobi(end));
fprintf(fileID, '    residuum_norm_Gauss_Seidel = %e;\n', residuum_norm_Gauss_Seidel(end));
fprintf(fileID, 'end\n');
fclose(fileID);


% Wykresy norm residuów
figure;

% Wykres dla metody bezpośredniej
subplot(3,1,1);
semilogy(0:length(residuum_norm_direct)-1, residuum_norm_direct, '-o', 'LineWidth', 2);
xlabel('Iteracja');
ylabel('Norma residuum');
title('Metoda bezpośrednia');
grid on;

% Wykres dla metody Jacobiego
subplot(3,1,2);
semilogy(0:length(residuum_norm_Jacobi)-1, residuum_norm_Jacobi, '-o', 'LineWidth', 2);
xlabel('Iteracja');
ylabel('Norma residuum');
title('Metoda Jacobiego');
grid on;

% Wykres dla metody Gaussa-Seidla
subplot(3,1,3);
semilogy(0:length(residuum_norm_Gauss_Seidel)-1, residuum_norm_Gauss_Seidel, '-o', 'LineWidth', 2);
xlabel('Iteracja');
ylabel('Norma residuum');
title('Metoda Gaussa-Seidla');
grid on;

% Zapisanie wykresów do pliku PNG
print('solve.png', '-dpng');