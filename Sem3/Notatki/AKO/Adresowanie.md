---
aliases:
  - Tryby adresowania
---
Adres logiczny = rejestr segmentowy + adres efektywny
# Natychmiastowe
Adresowanie literałem, hardcoded w [[Instrukcja#Kod rozkazu|rozkaz]].
# Bezpośrednie
W [[Instrukcja#Kod rozkazu]] jest wpisany literał [[Pamięć|adresu]].
# Indeksowe
[[Adresowanie#Bezpośrednie]] z przesunięciem o liczbę bajtów.
## Bazowo-indeksowe

^ebde66

**ze skalowaniem**: kompozycja operacji matematycznych na rejestrach: *bazowym* (dowolny rejestr 32bit - początek tablicy) i *indeksowym* (**NIE ESP**, 32bit - klucz dla indeksu, podstawiany do wzoru).

Adres efektywny = `Bazowy + 1/2/4/8 * Indeksowy ± const` ^5bb429
>[!tip]
>Aby osiągnąć np. ujemną wartość rejestru bazowego należy wpierw użyć instrukcji `neg` przed adresowaniem.

---
# Pośredni
>[!error] Nieobecny w architekturze Intel x86

# z autoinkrementacją
>[!error] Nieobecny w architekturze Intel x86

*zwiększ zawartość rejestru indeksowego o ilość odczytanych bajtów*
`mov eax, (ebx)+`
## z autodekrementacją
`mov eax, -(ebx)`

# Efektywne
Adres lokacji pamięci 