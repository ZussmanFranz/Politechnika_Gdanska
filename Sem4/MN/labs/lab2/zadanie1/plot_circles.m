function plot_circles(a, b, circles)
    % PLOT_CIRCLES rysuje prostokąt o wymiarach [0,a] x [0,b] oraz okręgi
    % zawarte w macierzy circles (każdy wiersz: [X, Y, R])
    
    figure;                 % nowy wykres
    axis equal              % jednakowa skala dla osi x i y
    axis([0 a 0 b])         % ograniczenie widoku do prostokąta
    hold on                 % umożliwia rysowanie wielu okręgów na jednym wykresie
    
    n = size(circles, 1);
    for i = 1:n
        X = circles(i, 1);
        Y = circles(i, 2);
        R = circles(i, 3);
        plot_circle(X, Y, R);   % zakładamy, że funkcja plot_circle jest dostępna
        pause(0.1);             % opcjonalnie: obserwacja rysowania kolejnych okręgów
    end
    hold off
end
    
function plot_circle(X, Y, R)
    % R - promień okręgu
    % X - współrzędna x środka okręgu
    % Y - współrzędna y środka okręgu
    theta = linspace(0,2*pi);
    x = R*cos(theta) + X;
    y = R*sin(theta) + Y;
    plot(x,y)
end