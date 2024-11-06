---
aliases:
  - Computation model
---
# Maszyna Turinga
# Rachunek lambda
https://pl.wikipedia.org/wiki/Teoria_oblicze%C5%84

$\lambda$x -> x² <=> funkcja, która zwraca kwadrat argumentu

![[System formalny]]

Zbiór wszystkich wyrażeń $\Lambda$
>[!info] Definicja $\Lambda$
>1. Wszystkie zmienne należą do $\Lambda$
>2. Jeśli x jest zmienną i M należy do $\Lambda$, to funkcja zwracająca M też należy.
>3. Jeśli M i N należą do $\Lambda$, to M(N) też należy.

Konwencje zapisu:
1. pomijamy nawiasy zewnętrzne
2. $\lambda$x -> ($\lambda$y -> M) <=> $\lambda$xy -> M
3. (MN)P <=> MNP
4. #todo slajd
