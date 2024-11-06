---
aliases:
  - Stack
---
Stos służy do tymczasowego przechowywania danych, które nie mieszczą się w rejestrach.

>[!important] Stos rośnie w stronę malejących adresów

Miejsce na stos jest alokowane automatycznie, wskaźnik mamy w [[Rejestry|rejestrze]] `esp`.

[[Najważniejsze instrukcje#push/pop]] ^eba4d0

>[!warning] Stack pointer powinien **zawsze** być podzielny przez 4!
>Pushować tylko wielkości 4-bajtowe! Tryb 32bitowy będzie ostrzegał i nie puści pushowania mniejszych rejestrów.
>**Ignorowanie ostrzeżeń grozi [[Stos#^77e56d|niewyrównaniem stosu]]**!

>[!warning] Stos ma być wyrównany!
>Stack pointer trzeba przywrócić do zastanej wartości pod koniec wykonywania programu. Na stosie znajduje się [[Podprogram#Lokalna pamięć podprogramu wołanego|adres powrotu programu]].

^77e56d

>[!warning] Pop nie usuwa danych, ale...
>...ta pamięć już do programu nie należy! [[Przerwanie systemowe]] może niespodziewanie przywłaszczyć obszar pamięci który jeszcze przed chwilą był nasz. Dostęp spowoduje wtedy trudno replikowalny [[Wyjątek]].

>[!note] Abstrakcja
>W [[Tryby adresowania#Chroniony]], [[OS]] może podmieniać nam stos w zależności od obecnego uprzywilejowania.

![[Najważniejsze instrukcje#^909b56]]

# Wywoływanie funkcji
>[!warning] Kto pushnął ten popuje
> Obowiązek oczyszczenia stosu leży na wołającym.
> ```asm
> push ... ; a
> push ... ; b
> call ...
> 
> add esp, (rozmiar a i b) ; przesuwamy wskaźnik stosu 

W przypadku [[Przekaz argumentów#Przez rejestr]] przydaje się [[Rejestry#^2aaba7|rejestr `ebp`.]]
![[Rejestry#^97449a]]

>[!info] Funkcja musi zachować wartość rejestrów:
>esp, ebp, edi, edi, ebx
>(Standard C)
>>[!warning] Można modyfikować ecx, edx
>>Na przykład [[Najważniejsze instrukcje#loop|`loop`]] dekrementuje ecx

^a7507b

![[Interfejs ABI]]
