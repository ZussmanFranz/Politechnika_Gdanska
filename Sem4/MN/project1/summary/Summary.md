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

Sygnały transakcyjne generowane są poprzez przecięcia linii MACD oraz sygnału. Przecięcie linii MACD od dołu przez linię sygnału sugeruje sygnał kupna, a przecięcie od góry – sygnał sprzedaży. Przecięcie odbywa się przy zmianie znaku kolejnych słupków histogramu odnośnie poprzednich słupków.

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

Na osi X można zauważyć tak zwane **record indexes**, czyli indeksy notowań, co w praktyce oznacza numer dnia od początku notowania danej kryptowaluty.

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

Na wykresie widoczne są poszczególne transakcje wraz z osiągniętym zyskiem lub stratą wyrażoną w procencie kapitału przed transakcją. Widoczne są zarówno transakcje wyjątkowo zyskowne, jak i stratne, co podkreśla zmienność strategii MACD na rynku kryptowalut.

Większość strat oscyluje w okolicach –20%. Po stronie zysków można zauważyć grupę transakcji o dodatnich wynikach w zakresie od kilku do kilkudziesięciu procent, przy czym najwyższa zaobserwowana wartość to około +22%. Nie widać tu jednak żadnych ekstremalnie wysokich zysków, co oznacza, że ogólny wynik strategii nie jest zdominowany przez pojedynczą, wyjątkowo dochodową transakcję.

Po prawej stronie widać wykres, obliczający sumaryczną proporcję zyskanych i straconych dolarów. Jak widać, różnica zyskanej i straconej sumy wynosi około 5%. To jest spowodowane tym faktem, że historia cen na badanym odcinku demonstruje jak globalne podniesienie, tak i globalny spadek.  
### 5.2 Krzywa kapitału w czasie

![[USD_capital_history.png]]

Powyższy wykres przedstawia zmiany kapitału początkowego (`1000 USD`) w całym okresie analizy (200 dni, `2021-07-20` - `2022-02-04`) w porównaniu do tak zwanego "Lazy trading" (czyli notowania wartości początkowego kapitału SOL w każdym odpowiednim punkcie, co pozwala ocenić efektywność algorytmu MACD nie uwzględniając wahanie ceny za jednostkę SOL). Wykres ten obrazuje ogólną efektywność strategii inwestycyjnej opartej na wskaźniku MACD, pokazując zarówno okresy znaczących zysków, jak i dużych spadków kapitału.

Przeprowadzono symulację strategii opartej na następujących założeniach:

- Kapitał początkowy: **1000 USD**
- Kapitał końcowy: **12665 USD**
- Całkowita stopa zwrotu: **1166%**
- "Leniwy" kapitał końcowy: **4798 USD**
- Przewaga MACD nad "Leniwym" algorytmem: **7867 USD** 
- Ilość transakcji: **60**

Tabela przykładowych transakcji wraz z wynikami (Profit/Loss %):

| #   | Buy Date   | Buy Price | Sell Date  | Sell Price | Profit (USD) | Profit (%) |
| --- | ---------- | --------- | ---------- | ---------- | ------------ | ---------- |
| 1   | 2021-07-20 | 23.46     | 2021-07-23 | 28.51      | 5.05         | 21.53%     |
| 2   | 2021-07-24 | 28.65     | 2021-07-26 | 28.22      | -0.43        | -1.50%     |
| 3   | 2021-07-27 | 28.14     | 2021-07-29 | 31.28      | 3.14         | 11.16%     |
| 4   | 2021-08-01 | 34.20     | 2021-08-03 | 34.11      | -0.09        | -0.26%     |
| 5   | 2021-08-05 | 37.37     | 2021-08-06 | 39.52      | 2.15         | 5.75%      |
| 6   | 2021-08-07 | 39.48     | 2021-08-09 | 38.69      | -0.79        | -2.00%     |
| 7   | 2021-08-11 | 41.66     | 2021-08-12 | 41.09      | -0.57        | -1.37%     |
| 8   | 2021-08-15 | 53.53     | 2021-08-16 | 62.15      | 8.62         | 16.10%     |
| 9   | 2021-08-18 | 72.79     | 2021-08-20 | 78.68      | 5.89         | 8.09%      |
| 10  | 2021-08-21 | 73.89     | 2021-08-22 | 72.75      | -1.14        | -1.54%     |

---

## 6. Szczegółowa analiza

Poniższe wykresy przedstawiają szczegółową analizę wyników strategii inwestycyjnej opartej na MACD:
## 6.1 Okres badany

![[summary_plot.png]]

## 6.2 Przykłady innych okresów
### 2021-01-01 : 2021-11-17
![[0_320.png]]
### 2021-01-01 : 2022-05-16
![[0_500.png]]
### 2022-05-16 : 2023-09-28
![[500_1000.png]]
### 2023-09-28 : 2024-09-29
![[1000_end.png]]

---
## 7. Podsumowanie i wnioski końcowe

Przeprowadzona analiza skuteczności strategii opartej na wskaźniku MACD dla kryptowaluty Solana (SOL) pozwala na wyciągnięcie następujących wniosków:

- **Wskaźnik MACD** okazał się szczególnie efektywny w warunkach silnych trendów wzrostowych, co było widoczne podczas dynamicznych wzrostów w 2021 roku. W takich okresach strategia generowała wysokie zyski.
- Strategia wykazuje jednak znaczne słabości w okresach silnych spadków i zwiększonej zmienności cenowej, co pokazała między innymi druga połowa okresu badanego.
- Pomimo ostatecznie wysokiego wyniku końcowego (**1166%** za cały analizowany okres), strategia cechowała się dużą zmiennością i znacznym ryzykiem, wynikającym głównie z dużych strat w pojedynczych transakcjach.

W celu poprawienia stabilności oraz efektywności strategii inwestycyjnej opartej na MACD zalecane jest:

- Zastosowanie dodatkowych filtrów potwierdzających sygnały MACD.
- Wprowadzenie bardziej zaawansowanego zarządzania kapitałem (np. Stop-Loss, Take-Profit), co może ograniczyć ryzyko znaczących strat.
- Uwzględnienie czynników fundamentalnych i rynkowych, które mogłyby zmniejszyć liczbę fałszywych sygnałów w okresach niestabilności rynku.

Podsumowując, MACD jest wartościowym narzędziem wspierającym decyzje inwestycyjne, jednak jego efektywność znacząco rośnie, gdy stosowany jest jako element szerszego, bardziej kompleksowego podejścia do analizy rynku kryptowalut.