Oznacza linijkę do której [[Proces kompilacji|kompilator]] wstawia obecnie kompilowany kod.

Dostęp odbywa się poprzez symbol `$`
`$+3eb0` -> "przesuń licznik lokacji o 3eb0"

```asm
text db '...'
length = $ - text
```
