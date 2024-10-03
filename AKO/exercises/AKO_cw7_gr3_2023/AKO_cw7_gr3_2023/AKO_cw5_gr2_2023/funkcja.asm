;Napisaæ podprogram w asemblerze ‘wyswietl_RAX’, 
;który wyœwietli na ekranie zawartoœæ rejestru rdx:rAX w postaci liczby dziRSIêtnej. 
;Zak³adamy, ¿e w rejestrach rdx:rAX znajduje siê 128-bitowa liczba binarna bez znaku.
;Cyfry uzyskiwane w trakcie kolejnych dzieleñ nale¿y zapisywaæ w 12-bajtowym 
;obszarze pamiêci zarezerwowanym na stosie.
;Podprogram jest podobny do opisanego w instrukcji laboratoryjnej do æw. 3,
;gdzie dane tymczasowe przechowywane s¹ w sekcji danych programu (nie na stosie).
;Opracowany podprogram w³¹czyæ do kompletnego programu w asemblerze, 
;w którym podprogram bêdzie kilkakrotnie wywo³ywany dla ró¿nych wartoœci argumentów.


public wyswietl_RAX

.data
; deklaracja tablicy 12-bajtowej do przechowywania
; tworzonych cyfr
znak db '1'
dzielnik dd 1
znaki db 12 dup (?)
;w0 dd 0
;w1 dd 0
;w2 dd 0
.code



wyswietl_RAX PROC
	push RBP
	mov RBP,RSP 
		


	sub RSP,36+2*4  ; rezerwacja zmiennej dynamicznej
	
	push RSI
	push RDI
	push RBX
;mov w2,RCX
	
	lea RCX,[RBP-44]		; adres w0
	
	movups [RCX],xmm0
	

	

	mov RAX,[RBP+12]
	mov [RCX+4],RAX
	mov RAX,[RBP+8]
	mov [RCX],RAX

	;mov RAX,[RBP+8]
	;mov RDI,RBP
	;sub RDI,34
	lea RDI,[RBP-34]
		
	mov RSI, 32 ; indeks w tablicy 'znaki' 
	mov RBX, 10 ; dzielnik równy 10
konwersja: 
	mov RDX, 0 ; zerowanie starszej czêœci dzielnej 
	;mov RAX, w2
	;div RBX ; dzielenie przez 10, reszta w RDX, 
			; iloraz w RAX 
    ;mov w2,RAX

	mov RAX, [RCX+4]
	div RBX ; dzielenie przez 10, reszta w RDX, 
			; iloraz w RAX 
    mov [RCX+4],RAX

	; reszta r1 jest w RDX
	mov RAX,[RCX]  ; a0 = w0
	div RBX
	mov [RCX],RAX

	add dl, 30H ; zamiana reszty z dzielenia na kod ASCII 
	mov [RDI][RSI], dl; zapisanie cyfry w kodzie ASCII
	dec RSI ; zmniejszenie indeksu 
	or RAX,[RCX+4]
	;or RAX,w2
	;cmp RAX, 0 ; sprawdzenie czy iloraz = 0 
	jne konwersja ; skok, gdy iloraz niezerowy
; wype³nienie pozosta³ych bajtów spacjami i wpisanie 
; znaków nowego wiersza 
wypeln: 
	or RSI, RSI		; cmp RSI,0
	jz wyswietl ; skok, gdy RSI = 0 
	mov byte PTR [RDI][RSI], 20H ; kod spacji 
	dec RSI ; zmniejszenie indeksu 
	jmp wypeln 

wyswietl: 
	mov byte PTR [RDI+0], 0AH ; kod nowego wiersza 
	mov byte PTR [RDI][33], 0AH ; kod nowego wiersza
; wyœwietlenie cyfr na ekranie 
	push dword PTR 34 ; liczba wyœwietlanych znaków 
	;push dword PTR OFFSET znaki ; adres wyœw. obszaru 
	push RDI
	push dword PTR 1; numer urz¹dzenia (ekran ma numer 1) 

	;call __write ; wyœwietlenie liczby na ekranie 
	add RSP, 12 ; usuniêcie parametrów ze stosu



	pop RBX
	pop RDI
	pop RSI

	add RSP,44	; usuniêcie zmiennej dynamicznej
	pop RBP
	ret
wyswietl_RAX ENDP


END
