Architekturę systemu opisuje się **atrybutami**. Zbiór atrybutów nazywamy **modelem programowym**. (Architektura zbioru [[Instrukcja|instrukcji]] [ISA](https://en.wikipedia.org/wiki/Instruction_set_architecture))
Atrybuty architektury:
- Zbiór instrukcji
- Dostępne rejestry
- Typy i rozmiary operandów
- Tryby adresowania 
- Instrukcje sterowania przepływem
- Kodowanie instrukcji
- Alignment (wyrównywanie) adresów
- Klasy odwołań do pamięci ([[Register-memory architecture]], [[Load-store architecture]])

>[!important] Model a organizacja
>Procesory Intel i AMD mają *ten sam* model programowy. Różnią się *organizacją* (implementacją hardware'ową). 

>[!tip] 
>Niektóre modele wspierają zmienne rozmiary kodów instrukcji, tj. mają instrukcje zarówno jedno- jak i np. dwubajtowe.
# Historia modeli programowych
## x86
x86, x86_64 to modele programowe. x86: 16/32-bit, x86_64: 32/64-bit [[Rejestry]].
## IA
Intel rozwinął własną linię procesorów. Wkrótce narodziły się architektury IA32, IA64, wyspecjalizowane dla serwerów. Modele serii IA są kompatybilne wstecznie, ku wygodzie użytkownika i zmorze nas, którzy musimy się uczyć okrętnych rozwiązań.
%%
# Opcode
>[!error] #todo

%%