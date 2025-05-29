function [x, y, z, zmin, lake_volume] = compute_lake_volume_monte_carlo()
    % Wyznacza objętość jeziora metodą Monte Carlo.
    %
    % x/y/z - wektory wierszowe, które zawierają współrzędne x/y/z punktów
    %       wylosowanych w celu wyznaczenia przybliżonej objętości jeziora
    % zmin - minimalna dopuszczalna wartość współrzędnej z losowanych punktów
    % lake_volume - objętość jeziora wyznaczona metodą Monte Carlo

    N = 1e6;
    x = 100*rand(1,N); % [m]
    y = 100*rand(1,N); % [m]
    
    zmin = -100;

    z = zmin + (-zmin) * rand(1, N); 

    V_bounding_box = 100 * 100 * (-zmin); % [m^3]

    lake_depths_at_xy = get_lake_depth(x, y);
    
    N1_points_above_bottom = sum(z > lake_depths_at_xy);

    lake_volume = (N1_points_above_bottom / N) * V_bounding_box;
end