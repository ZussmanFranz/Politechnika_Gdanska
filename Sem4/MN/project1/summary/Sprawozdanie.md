# Sprawozdanie: Analiza wskaźnika MACD dla kryptowaluty Solana (SOL)

**Autor:** Yauheni Pyryeu
**Data:** 26.03.2026 r.

## 1. Wstęp

### 1.1 Cel projektu

Celem projektu było przeprowadzenie szczegółowej analizy wskaźnika MACD (**Moving Average Convergence Divergence**) na przykładzie kryptowaluty Solana (SOL). Analiza obejmowała implementację wskaźnika, wizualizację wyników, generowanie sygnałów transakcyjnych oraz symulację strategii inwestycyjnej opartej na MACD.

### 1.2 Opis wskaźnika MACD

Wskaźnik MACD składa się z trzech podstawowych elementów:

- **Linia MACD**: różnica między 12-dniową a 26-dniową wykładniczą średnią kroczącą (EMA).
$$
MACD(i) = EMA_{12}(i) - EMA_{26}(i)
$$
- **Linia sygnału (Signal Line)**: 9-dniowa wykładnicza średnia krocząca wartości MACD.
$$
SIGNAL(i) = EMA_{9}(MACD(i))
$$
- **Histogram MACD**: różnica między linią MACD a linią sygnału.

Sygnały transakcyjne generowane są poprzez przecięcia linii MACD oraz sygnału. Przecięcie linii MACD od dołu przez linię sygnału sugeruje sygnał kupna, a przecięcie od góry – sygnał sprzedaży.

### 1.3 Wykładnicza średnia krocząca (EMA)

Podstawą do obliczania wskaźnika MACD są wykładnicze średnie kroczące (EMA – Exponential Moving Average). EMA jest typem średniej, która nadaje większą wagę najnowszym danym cenowym, co pozwala na szybszą reakcję na bieżące zmiany cen w porównaniu do zwykłej średniej ruchomej (SMA).

Wartość EMA w danym dniu $i$ obliczana jest na podstawie następującego wzoru:

$$
EMA_N(i) = \alpha*x_i + (1-\alpha)\times EMA_N(i-1)
$$

gdzie:

- $x_i$​ – cena zamknięcia w bieżącym dniu (lub okresie) $i$,
- $EMA_N(i-1)$ – wartość EMA z dnia poprzedniego $i-1$,
- $N$ – liczba okresów branych pod uwagę przy obliczeniach EMA,
- $\alpha$ – współczynnik wygładzający, obliczany według wzoru:
$$\alpha = \frac{2}{N + 1}$$

EMA może być również przedstawiona w formie rozwiniętej jako średnia ważona wszystkich wcześniejszych cen zamknięcia:
$$
EMA_N(i) = \frac{x_i + (1-\alpha)x_{i-1} + (1-\alpha)^2x_{i-2} + ...+(1-\alpha)^ix_0}{1+(1-\alpha)+(1-\alpha)^2+...+(1-\alpha)^i}
$$

gdzie wyraźnie widać, że współczynnik wagowy cen maleje wykładniczo w miarę oddalania się w czasie od bieżącego okresu.

Im krótszy okres $N$, tym większą wagę EMA przykłada do najnowszych danych cenowych, co zwiększa czułość wskaźnika na krótkoterminowe zmiany cenowe.

---

## 2. Dane

Analizę przeprowadzono na podstawie dziennych cen zamknięcia kryptowaluty Solana (SOL) w okresie od początku 2021 do pierwszego kwartału 2024 roku. Dane zostały pobrane ze [źródła](https://www.kaggle.com/datasets/gokberkkozak/solana-price-history-sol-usd) w formacie CSV.

---

## 3. Analiza wykresów cenowych i wskaźnika MACD

### 3.1 Wykres cenowy kryptowaluty SOL

W analizowanym okresie ceny SOL doświadczyły dwóch dużych cykli wzrostowych oraz spadkowych. Maksymalna cena przekroczyła 250 USD w 2021 roku, po czym nastąpiła korekta i ponowny wzrost cen w 2024.

![[SOL_full_price_history.png]]
![[SOL_price_history.png]]
### 3.2 Wykres MACD oraz linii sygnału

Na poniższym wykresie widoczne są linie MACD oraz sygnału, które wskazują na sygnały kupna i sprzedaży w kluczowych momentach cenowych.

![[MACDandSIGNAL.png]]

## Przykładowy fragment
Na poniższym wykresie przedstawione pierwsze 10 punktów oryginalnego wykresu "MACD and Signal".

![[MACDandSIGNAL_example.png]]

### 3.3 Wykres histogramu MACD

Histogram MACD wskazuje siłę ruchów cenowych, obrazując dynamiczne zmiany trendu.

![[MACDminusSIGNAL.png]]

## Przykładowy fragment
Na poniższym wykresie przedstawione pierwsze 10 punktów oryginalnego wykresu "MACD - Signal".

![[MACDminusSIGNAL_example.png]]

---

## 4. Analiza sygnałów transakcyjnych

Na poniższym wykresie przedstawiono wygenerowane sygnały kupna i sprzedaży dla całego analizowanego okresu.

![[BUY_SELL_signals.png]]

## Przykładowy fragment
Na poniższym wykresie przedstawione pierwsze 10 punktów oryginalnego wykresu "SOL Price History".

![[BUY_SELL_example.png]]

Można zauważyć, że wskaźnik MACD generował zarówno zyskowne jak i stratne sygnały transakcyjne, co wynikało z charakterystycznego opóźnienia wskaźnika w stosunku do realnych ruchów cenowych.

---

## 5. Symulacja strategii inwestycyjnej na podstawie MACD

Poniższe wykresy przedstawiają szczegółowe wyniki symulacji transakcji wykonanych na podstawie sygnałów MACD dla kryptowaluty Solana:

### 5.1 Zysk/Strata na pojedynczą transakcję

![[profits.png]]

Na wykresie widoczne są poszczególne transakcje wraz z osiągniętym zyskiem lub stratą wyrażoną w dolarach. Widoczne są zarówno transakcje wyjątkowo zyskowne, jak i stratne, co podkreśla zmienność strategii MACD na rynku kryptowalut.

Na wykresie widać rozkład procentowy zysków i strat z poszczególnych transakcji. Większość strat oscyluje w okolicach –20%, choć niektóre sięgają nawet –60%. Po stronie zysków można zauważyć grupę transakcji o dodatnich wynikach w zakresie od kilku do kilkudziesięciu procent, przy czym najwyższa zaobserwowana wartość to około +80%. Nie widać tu jednak żadnych ekstremalnie wysokich zysków, co oznacza, że ogólny wynik strategii nie jest zdominowany przez pojedynczą, wyjątkowo dochodową transakcję.

### 5.2 Krzywa kapitału w czasie

![[USD_capital_history.png]]

Poniższy wykres przedstawia zmiany kapitału początkowego (1000 USD) w całym okresie analizy (2021–2024). Wykres ten obrazuje ogólną efektywność strategii inwestycyjnej opartej na wskaźniku MACD, pokazując zarówno okresy znaczących zysków, jak i dużych spadków kapitału.

Z wykresu Equity Curve można wyciągnąć następujące wnioski:

- **2021 rok:** Wyraźny i szybki wzrost kapitału do około 15 000 USD, związany z dynamicznym wzrostem ceny SOL.
- **2022 rok:** Bardzo silne obsunięcie kapitału (drawdown przekraczający 80%), co ukazuje wysokie ryzyko inwestowania w kryptowaluty.
- **2023 rok:** Początek powrotu do zysków, z powolnym, ale wyraźnym odrabianiem wcześniejszych strat.
- **2024 rok:** Dalszy umiarkowany wzrost kapitału, co sugeruje stabilizację strategii.

Przeprowadzono symulację strategii opartej na następujących założeniach:

- Kapitał początkowy: **1000 USD**
- Koszty transakcyjne: **0,1%**
- Poślizg cenowy: **0,1%**

Wyniki symulacji:

- **Kapitał końcowy:** **35 323,45 USD**
- **Całkowita stopa zwrotu:** **3432,35%**
- **Maksymalny drawdown:** **-82,86%**
- **Ilość transakcji:** **49**

Tabela przykładowych transakcji wraz z wynikami (Profit/Loss %):

| Data zakupu | Cena zakupu | Data sprzedaży | Cena sprzedaży | Zysk/Strata (%) |
| ----------- | ----------- | -------------- | -------------- | --------------- |
| 2021-01-03  | 2.187       | 2021-01-21     | 2.994          | +26.87 %        |
| 2021-01-30  | 4.222       | 2021-02-17     | 8.222          | +48.6 %         |
| 2021-07-24  | 28.679      | 2021-09-14     | 158.761        | +81.92%         |
| 2022-05-21  | 50.30       | 2022-06-14     | 29.480         | -70.79 %        |
| 2023-01-02  | 11.291      | 2023-01-28     | 23.986         | +52.88 %        |
| 2024-02-28  | 119.09      | 2024-03-23     | 172.547        | +30.91 %        |

---

## 6. Szczegółowa analiza

Poniższe wykresy przedstawiają szczegółową analizę wyników strategii inwestycyjnej opartej na MACD:

![[summary_plot.png]]

---
## 7. Podsumowanie i wnioski końcowe

Przeprowadzona analiza skuteczności strategii opartej na wskaźniku MACD dla kryptowaluty Solana (SOL) pozwala na wyciągnięcie następujących wniosków:

- **Wskaźnik MACD** okazał się szczególnie efektywny w warunkach silnych trendów wzrostowych, co było widoczne podczas dynamicznych wzrostów w 2021 roku. W takich okresach strategia generowała wysokie zyski, osiągając roczną stopę zwrotu na poziomie aż **1403,34%**.
- Strategia wykazuje jednak znaczne słabości w okresach silnych spadków i zwiększonej zmienności cenowej, co pokazał rok 2022, kiedy maksymalny drawdown wyniósł aż **–82,86%**, a roczna stopa zwrotu spadła do **–77,78%**.
- W latach 2023–2024 nastąpiła stopniowa stabilizacja wyników, charakteryzująca się umiarkowanymi, lecz konsekwentnymi wzrostami. Świadczy to o możliwości częściowego odzyskiwania strat po dużych obsunięciach kapitału, jednak podkreśla również potrzebę lepszego zarządzania ryzykiem.
- Pomimo ostatecznie wysokiego wyniku końcowego (**3432,35%** za cały analizowany okres), strategia cechowała się dużą zmiennością i znacznym ryzykiem, wynikającym głównie z dużych strat w pojedynczych transakcjach.

W celu poprawienia stabilności oraz efektywności strategii inwestycyjnej opartej na MACD zalecane jest:

- Zastosowanie dodatkowych filtrów potwierdzających sygnały MACD.
- Wprowadzenie bardziej zaawansowanego zarządzania kapitałem (np. Stop-Loss, Take-Profit), co może ograniczyć ryzyko znaczących strat.
- Uwzględnienie czynników fundamentalnych i rynkowych, które mogłyby zmniejszyć liczbę fałszywych sygnałów w okresach niestabilności rynku.

Podsumowując, MACD jest wartościowym narzędziem wspierającym decyzje inwestycyjne, jednak jego efektywność znacząco rośnie, gdy stosowany jest jako element szerszego, bardziej kompleksowego podejścia do analizy rynku kryptowalut.