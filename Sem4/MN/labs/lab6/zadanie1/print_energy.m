function print_energy()
    % Wczytuje z pliku energy_2025.mat strukturę energy_2025 i przedstawia
    % jej zawartość.

    load energy_2025

    countries = {'Brazil', 'China', 'Czechia', 'France', 'Germany', 'India',...
        'Italy', 'Latvia', 'Poland', 'Slovakia', 'Spain', 'Sweden', 'USA',...
        'Ukraine', 'United_Kingdom'};
    sources = {'Bioenergy', 'Coal', 'Gas', 'Hydro', 'Nuclear',...
        'Other_Fossil', 'Other_Renewables', 'Solar', 'Wind'};

    for cid=1:length(countries)
        country = countries{cid};
        for sid=1:length(sources)
            source = sources{sid};
            if isfield(energy_2025, country) &&...
                    isfield(energy_2025.(country), source)
                y_original = energy_2025.(country).(source).EnergyProduction;
                tt = energy_2025.(country).(source).Dates;
                fprintf('%-30s | liczba danych: %5d\n',...
                    [country, '.', source], length(y_original));
            end
        end
    end

end
