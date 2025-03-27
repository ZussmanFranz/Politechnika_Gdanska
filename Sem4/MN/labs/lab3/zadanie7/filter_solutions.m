function [residuum_norm_direct, residuum_norm_Jacobi, residuum_norm_Gauss_Seidel] = filter_solutions()
%   residuum_norm_direct - norma residuum dla rozwiązania metodą bezpośrednią
%   residuum_norm_Jacobi - norma residuum dla rozwiązania metodą Jacobiego
%   residuum_norm_Gauss_Seidel - norma residuum dla rozwiązania metodą Gaussa-Seidelea

    residuum_norm_direct = 7.086626e-13;
    residuum_norm_Jacobi = NaN;
    residuum_norm_Gauss_Seidel = 6.436735e+10;
end
