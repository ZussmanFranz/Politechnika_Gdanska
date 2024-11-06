# mov
`mov gdzie(rejestr) co(literał/rejestr/pamięć)`
NIE MA `mov pamięć pamięć`!
`add`, `sub`

W większości modeli adres zapisany pod zmienną np. `dane` zapisuje się bez `[]`
> `mov rax dane`

## movzx
Używany do przemieszczania danych do większego rejestru. **Zeruje** wszystkie starsze bity.
## movsx
Jak `movsx`, tylko używa **jedynek**. Zachowuje wartośč liczby w U2.

# add/sub
...oraz wszystkie inne obliczenia dwuargumentowe

`add co_i_dokąd do_czego`
Jak odwołać się do pamięci?
> `[adres]`, np. `[100h]`

## adc
**dodatkowo** dodaje do wyniku [[Flagi|flagę carry]].

# mul/div
Wyjątkowo mnożenie jest jednoargumentowe. W zależności od rozmiaru czynnika wybierane są [[Rejestry|rejestry]] do odczytu i zapisu:
8-bit: `arg * al` -> `ax`
16-bit: `arg * ax` -> `eax`
32-bit: `arg * eax`->`rax`
64-bit: `arg * rax`->`rdx:rax` (młodsze bity w `rax`, starsze bity w `rdx` ([[Endian#Big endian|big endian]]))

`div ebx` = $\frac{edx:eax}{ebx}$ -> iloraz: eax, reszta: edx

# lea
: *load effective address*
![[Adresowanie#^5bb429]]

`lea ebx, [tag+edi+1]` 
<=>
```
mov ebx, offset tag
add ebx, edi
add ebx, 1
```

# push/pop
Wepchnij/zdejmij wartość na [[Stos]]. Potrzebne przy wywoływaniu funkcji.
# call
Wywołaj [[Podprogram]] (zaciągnięty makrem(?) `extern`)
`call funkcja`
1. odkłada adres funkcji
2. skok bezwarunkowy
3. wykonuje do napotkania `ret`
4. zczytuje ze stosu adres powrotu i wpisuje go do `eip`

>[!tip] Nie ma `mov eip`
>Aby włożyć coś do `eip` zrób:
>```asm
>push coś
>ret
>```

^909b56

# ret
Wczytuje adres powrotu ze stosu i wykonuje skok bezwarunkowy.
# db
*define byte*. `db dana, ... dana`
# nop
*no operation*. Pusty przebieg procesora.
# bswap
Zmienia [[Endian|Endianowość]] rejestru.
#
---
# Rozkazy sterujące
Realizują [[Flow control|Kontrolę przepływu]].
## skoki
### Bezpośrednie
%% #todo slajd z tabelą zmian w rejestrze flag różnych jumpów %% 
W [[Kod maszynowy|kodzie maszynowym]] zazwyczaj zajmuje 2 bajty: [[Instrukcja#Kod rozkazu]] i *zakres skoku*. Współczesne kompilatory w miarę potrzeby rozszerzają zakres skoku do 4 bajtów. Cała instrukcja zajmuje wtedy 6.
### Pośrednie
Zamiast etykiet używają *adresów zawartych w podanym rejestrze* lub w *obszarze danych*. Innymi słowy instrukcja docelowa skoku jest zmienną. Nadpisują `eip`. Przydatne m.in. przy polimorfizmie.
## loop

>[!warning] `loop` nie rozszerza swojego zakresu!

>[!info] `loop` używa rejestru `ecx`
>`loop` działa w dwóch krokach wykonywanych **w ustalonej kolejności**:
>1. dekrementacja ecx
>2. przerwanie jeżeli ecx = 0
>
>>[!warning] [[Stos#^a7507b]] 
>>Jeżeli [[Podprogram|funkcja]] wywoływana w ramach pętli używa `ecx`, nie ma obowiązku przywrócenia zastanej wartości!

>[!info] `loop` nie ustawia żadnych [[Flagi|flag]]
>Nawet jeżeli dekrementacja wywoła overflow 
## SET
np. `setc ax` "jeżeli carry, wpisz 1"
%% #todo research instrukcje z grupy set %%

## INT
interrupt - [[Podprogram]] systemowy. 
>[!warning] Nie mylić z [[Przerwanie systemowe]]!
> *Obsługa* przerwań i podprogramów jest analogiczna, ale to różne rzeczy.

Ślad podprogramu systemowego na [[Stos]]: eip, cs, flagi


# operacje bitowe
#todo