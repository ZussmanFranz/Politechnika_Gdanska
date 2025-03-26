close all
format compact

vN = 100:100:800;

[A,b,x,vec_time_direct] = benchmark_solve_direct(vN);

% Wykres zależności czasu od rozmiaru macierzy
figure;
plot(vN, vec_time_direct, '-o', 'LineWidth', 2);
xlabel('Rozmiar macierzy N');
ylabel('Czas obliczeń (s)');
title('Czas rozwiązania metodą LU w zależności od rozmiaru macierzy');
grid on;

% Zapis wykresu do pliku
print('zadanie2.png', '-dpng');
