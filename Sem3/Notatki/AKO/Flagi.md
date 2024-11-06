---
aliases:
  - Rejestr stanu procesora
  - Rejestr flag
  - Rejestr znaczników
---


# Rejestr stanu procesora
> Rejestr znaczników/flag

- Bit/flaga przeniesienia *carry flag* (`CF`, 0)
- Znacznik zera (`ZF`, 6)
- `DF` o sposobie [[Przesuwanie|przesuwania]]
- `SF` flaga znaku
- `PF` flaga parzystości
- `OF`
- itp.
%% #todo zmienić kolejność flag zgodnie z bitami rejesstru #todo extract %%
Każdy bit odpowiada jakiejś fladze instrukcji dopiero co wykonanej. 
>[!warning] Nie wszystkie instrukcje wpływają na flagi!

Bity 12-21 są użyteczne dla systemu operacyjnego.
np. [[Mnemonik]] `CPUID` dostępny jeśli bit 21 jest `1`.
## Rozkazy zmiany
`clc` zmienia `CF` na 0, `stc` na 1.
`pushf`, `popf` dumpują/ściągają flagi na/ze [[Stos|stosu]].