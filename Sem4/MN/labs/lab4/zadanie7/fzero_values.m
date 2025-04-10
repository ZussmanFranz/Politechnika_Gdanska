function [x1, y1, x2, y2] = fzero_values()
    % x1 - miejsce zerowe funkcji tangens obliczone przez fzero dla x=4.5
    % x2 - miejsce zerowe funkcji tangens obliczone przez fzero dla x=6
    % y1 - wartość funkcji tan wyznaczona dla argumentu x1
    % y2 - wartość funkcji tan wyznaczona dla argumentu x2

    options = optimset('Display','iter');
    
    [x1, y1] = fzero(@tan,4.5, options);
    [x2, y2] = fzero(@tan,6.0, options);

    disp(x1)
    disp(x2)
    
    disp(tan(x1))
    disp(y1)

    disp(tan(x2))
    disp(y2)

    % Rysowanie wykresów funkcji tangens w okolicach miejsc zerowych
    figure;

    % Wykres dla x1
    subplot(2, 1, 1);
    x_vals1 = linspace(4, 5, 1000);
    y_vals1 = tan(x_vals1);
    plot(x_vals1, y_vals1, 'b-', 'LineWidth', 1.5);
    hold on;
    plot(x1, y1, 'ro', 'MarkerSize', 8, 'LineWidth', 2);
    title('Miejsce zerowe funkcji tangens w okolicy x = 4.5');
    xlabel('x');
    ylabel('tan(x)');
    hold off;
    grid on;
    ylim([-10, 10]);

    % Wykres dla x2
    subplot(2, 1, 2);
    x_vals2 = linspace(5.5, 6.5, 1000);
    y_vals2 = tan(x_vals2);
    plot(x_vals2, y_vals2, 'b-', 'LineWidth', 1.5);
    hold on;
    plot(x2, y2, 'ro', 'MarkerSize', 8, 'LineWidth', 2);
    title('Miejsce zerowe funkcji tangens w okolicy x = 6');
    xlabel('x');
    ylabel('tan(x)');
    hold off;
    grid on;
    ylim([-10, 10]);

    % Zapisanie wykresu do pliku
    saveas(gcf, 'zadanie7.png');

end