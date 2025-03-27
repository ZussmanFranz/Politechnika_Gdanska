% Nie wczytuje danych z filtr_dielektryczny.mat i nie wyznacza rozwiązania analizy filtru mikrofalowego.

% Nadaje wartości parametrów zwracanych przez funkcję filter_solutions zgodne z 
% rezultatami uruchomienia funkcji zadanie7_solve.

function [residuum_norm_direct, residuum_norm_Jacobi, residuum_norm_Gauss_Seidel] = filter_solutions()
    % residuum_norm_direct - norma residuum dla rozwiązania metodą bezpośrednią
    % residuum_norm_Jacobi - norma residuum dla rozwiązania metodą Jacobiego
    % residuum_norm_Gauss_Seidel - norma residuum dla rozwiązania metodą Gaussa-Seidele'a
    
    residuum_norm_direct = [];
    residuum_norm_Jacobi = [];
    residuum_norm_Gauss_Seidel = [];
end