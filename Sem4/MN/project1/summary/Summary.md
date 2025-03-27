# Sprawozdanie: Analiza wskaźnika MACD dla kryptowaluty Solana (SOL)

**Autor:** Yauheni Pyryeu  
**Data:** 26.03.2025 r.



## 1. Wprowadzenie

### 1.1 Cel analizy

Niniejsza analiza koncentruje się na wskaźniku MACD (**Moving Average Convergence Divergence**) w kontekście kryptowaluty Solana (SOL). Celem badania było zrozumienie działania wskaźnika, jego implementacja, wizualizacja wyników, a także ocena skuteczności strategii inwestycyjnej opartej na sygnałach MACD.



### 1.2 Charakterystyka wskaźnika MACD

Wskaźnik MACD składa się z trzech kluczowych elementów:

- **Linia MACD**: różnica między 12-dniową a 26-dniową wykładniczą średnią kroczącą (EMA). $$ MACD(i) = EMA_{12}(i) - EMA_{26}(i) $$
- **Linia sygnału (Signal Line)**: 9-dniowa wykładnicza średnia krocząca wartości MACD. $$ SIGNAL(i) = EMA_{9}(MACD(i)) $$
- **Histogram MACD**: różnica między linią MACD a linią sygnału.

Sygnały transakcyjne są generowane w momencie przecięcia się linii MACD i sygnałowej. Gdy MACD przecina linię sygnałową od dołu, oznacza to sygnał kupna, natomiast przecięcie od góry sugeruje sygnał sprzedaży.

<div style="page-break-after: always;"></div>


### 1.3 Wykładnicza średnia krocząca (EMA)

Wartość EMA w danym dniu $i$ obliczana jest na podstawie następującego wzoru:

$$ EMA_N(i) = \alpha*x_i + (1-\alpha)\times EMA_N(i-1) $$

Gdzie: 
- $x_i$​ – cena zamknięcia w bieżącym dniu (lub okresie) $i$, 
- $EMA_N(i-1)$ – wartość EMA z dnia poprzedniego $i-1$, 
- $N$ – liczba okresów branych pod uwagę przy obliczeniach EMA, 
- $\alpha$ – współczynnik wygładzający, obliczany według wzoru:$$\alpha = \frac{2}{N + 1}$$
EMA może być również przedstawiona w formie rozwiniętej jako średnia ważona wszystkich wcześniejszych cen zamknięcia:
$$ EMA_N(i) = \frac{x_i + (1-\alpha)x_{i-1} + (1-\alpha)^2x_{i-2} + ...+(1-\alpha)^ix_0}{1+(1-\alpha)+(1-\alpha)^2+...+(1-\alpha)^i} $$
Współczynnik wagowy cen maleje wykładniczo w miarę oddalania się w czasie od bieżącego okresu. Im krótszy okres $N$, tym większą wagę EMA przykłada do najnowszych danych cenowych, co zwiększa czułość wskaźnika na krótkoterminowe zmiany cenowe.

---

## 2. Dane

Analiza obejmuje dane o cenach zamknięcia Solany (SOL) od początku 2021 r. do trzeciego kwartału 2024 r., pozyskane ze źródła [Kaggle](https://www.kaggle.com/datasets/gokberkkozak/solana-price-history-sol-usd) w formacie CSV.

---
<div style="page-break-after: always;"></div>
## 3. Analiza wykresów cenowych i wskaźnika MACD

### 3.1 Wykres cen SOL

Na całym okresie Solana przeszła przez dwa główne cykle wzrostów i spadków. Maksimum przekroczyło 250 USD w 2021 roku, po czym nastąpiła korekta i kolejne odbicie w 2024.

![[SOL_full_price_history.png]] ![[SOL_price_history.png]]

---
<div style="page-break-after: always;"></div>

### 3.2 Wskaźnik MACD i linia sygnałowa

Poniższy wykres przedstawia linie MACD oraz Signal, wskazujące kluczowe momenty kupna i sprzedaży.

![[MACDandSIGNAL.png]]
## Przykładowy fragment

Na poniższym wykresie przedstawione pierwsze 10 punktów oryginalnego wykresu "MACD and Signal".

![[MACDandSIGNAL_example.png]]

---
<div style="page-break-after: always;"></div> 
### 3.3 Histogram MACD

Histogram MACD ukazuje dynamikę trendu, obrazując siłę ruchów cenowych.

![[MACDminusSIGNAL.png]]
## Przykładowy fragment

Na poniższym wykresie przedstawione pierwsze 10 punktów oryginalnego wykresu "MACD - Signal".

![[MACDminusSIGNAL_example.png]]

---

<div style="page-break-after: always;"></div>
## 4. Sygnały transakcyjne

Na wykresie poniżej zaznaczono punkty kupna i sprzedaży dla całego okresu analizy.

![[BUY_SELL_signals.png]]
## Przykładowy fragment

Na poniższym wykresie przedstawione pierwsze 10 punktów oryginalnego wykresu "SOL Price History".

![[BUY_SELL_example.png]]

Można zauważyć, że MACD generował zarówno zyskowne, jak i stratne sygnały, wynikające z jego opóźnionej reakcji na zmiany cen.

---

<div style="page-break-after: always;"></div>
## 5. Symulacja strategii inwestycyjnej na podstawie MACD

### 5.1 Wyniki pojedynczych transakcji

![[profits.png]]

Wyniki pokazują dużą zmienność strategii – niektóre transakcje przynosiły duże zyski, inne straty. Maksymalny zaobserwowany zysk to ok. +22%, a większość strat oscylowała wokół -20%. Nie widać tu jednak żadnych ekstremalnie wysokich zysków, co oznacza, że ogólny wynik strategii nie jest zdominowany przez pojedynczą, wyjątkowo dochodową transakcję.

Po prawej stronie widać wykres, obliczający sumaryczną proporcję zyskanych i straconych dolarów. Jak widać, różnica zyskanej i straconej sumy wynosi około 5%. To jest spowodowane tym faktem, że historia cen na badanym odcinku demonstruje jak globalne podniesienie, tak i globalny spadek.

---
<div style="page-break-after: always;"></div>
### 5.2 Krzywa kapitału

![[USD_capital_history.png]]

- Okres analizy: **2021-07-20** - **2022-02-04**
- Kapitał początkowy: **1000 USD**
- Kapitał końcowy: **12665 USD**
- Całkowita stopa zwrotu: **1166%**
- "Leniwy" kapitał końcowy: **4798 USD**
- Przewaga MACD nad "Leniwym" algorytmem: **7867 USD**
- Ilość transakcji: **60**

Tabela przykładowych transakcji:

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

<div style="page-break-after: always;"></div>
## 6. Analiza szczegółowa

Poniższe wykresy przedstawiają szczegółową analizę wyników strategii inwestycyjnej opartej na MACD:

## 6.1 Okres badany

## **2021-07-20** - **2022-02-04**

![[summary_plot.png]]

---
<div style="page-break-after: always;"></div>

## 6.2 Przykłady innych okresów

### 2021-01-01 : 2021-11-17

![[0_320.png]]
<div style="page-break-after: always;"></div>

### 2021-01-01 : 2022-05-16

![[0_500.png]]
<div style="page-break-after: always;"></div>

### 2022-05-16 : 2023-09-28

![[500_1000.png]]
<div style="page-break-after: always;"></div>

### 2023-09-28 : 2024-09-29

![[1000_end.png]]

---

<div style="page-break-after: always;"></div>

## 7. Wnioski

Analiza wskaźnika MACD dla kryptowaluty Solana (SOL) pozwoliła na sformułowanie następujących wniosków:

- **Wskaźnik MACD** sprawdzał się szczególnie dobrze w okresach silnych trendów wzrostowych, co było widoczne zwłaszcza podczas dynamicznych zwyżek cen w 2021 roku. W takich momentach strategia przynosiła znaczące zyski.
- Wskaźnik wykazywał jednak istotne słabości w okresach gwałtownych spadków i podwyższonej zmienności rynkowej, co było zauważalne szczególnie w drugiej połowie badanego okresu.
- Mimo że końcowy wynik analizy był wysoki (**1166%** za cały analizowany okres), strategia charakteryzowała się dużą zmiennością oraz wysokim ryzykiem, głównie ze względu na istotne straty w pojedynczych transakcjach.

Aby zwiększyć stabilność i skuteczność podejścia opartego na MACD, warto rozważyć:

- Stosowanie dodatkowych filtrów weryfikujących sygnały generowane przez MACD (Na przykład $EMA_{90}$ dla wyznaczenia trendu globalnego).
- Wdrożenie bardziej zaawansowanych metod zarządzania kapitałem, takich jak Stop-Loss czy Take-Profit, aby ograniczyć ryzyko większych strat.
- Uwzględnienie czynników fundamentalnych oraz ogólnej sytuacji rynkowej, co mogłoby pomóc w redukcji liczby fałszywych sygnałów w niestabilnych warunkach rynkowych.

Podsumowując, MACD to przydatne narzędzie wspierające decyzje inwestycyjne, jednak jego efektywność znacząco wzrasta, gdy stanowi część bardziej kompleksowej analizy rynku kryptowalut.