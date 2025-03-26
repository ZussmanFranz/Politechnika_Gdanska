function [A,b,x,vec_time_direct] = benchmark_solve_direct(vN)
    % Pomiar czasu rozwiązania length(vN) równań macierowych metodą LU,
    % przy czym liczba zmiennych i-tego równania wynosi vN(i).
    % A - tablica komórkowa zawierająca zestaw macierzy A do równania macierzowego
    %       A{i}*x{i}=b{i}, gdzie size(A{i},1) = vN(i)
    % b - tablica komórkowa prawych stron równań A{i}*x{i}=b{i}
    % x - tablica komórkowa z rozwiązaniami równań A{i}*x{i}=b{i}
    % vec_time_direct(i) - czas wyznaczenia i-tego rozwiązania metodą LU
    
    
    A = cell(1, length(vN));
    b = cell(1, length(vN));
    x = cell(1, length(vN));
    vec_time_direct = zeros(1,length(vN));
    
    for i=1:length(vN)
        N = vN(i);
    
        [A{i},b{i}] = generate_matrix(N);
    
        tic
        
        [L, U, P] = lu(A{i});  % Faktoryzacja LU
        y = L \ (P * b{i});    % Podstawienie w przód
        x{i} = U \ y;          % Podstawienie wstecz
    
        vec_time_direct(i) = toc;
    end

    % Wykres zależności czasu od rozmiaru macierzy
    figure;
    plot(vN, vec_time_direct, '-o', 'LineWidth', 2);
    xlabel('Rozmiar macierzy N');
    ylabel('Czas obliczeń (s)');
    title('Czas rozwiązania metodą LU w zależności od rozmiaru macierzy');
    grid on;

    % Zapis wykresu do pliku
    print('zadanie2.png', '-dpng');
    
end