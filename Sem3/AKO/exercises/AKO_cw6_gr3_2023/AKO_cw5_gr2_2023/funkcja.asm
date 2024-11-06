;Napisaæ podprogram w asemblerze ‘wyswietl_EAX’, 
;który wyœwietli na ekranie zawartoœæ rejestru EDX:EAX w postaci liczby dziesiêtnej. 
;Zak³adamy, ¿e w rejestrach EDX:EAX znajduje siê 64-bitowa liczba binarna bez znaku.
;Cyfry uzyskiwane w trakcie kolejnych dzieleñ nale¿y zapisywaæ w X-bajtowym 
;obszarze pamiêci zarezerwowanym na stosie.
;Podprogram jest podobny do opisanego w instrukcji laboratoryjnej do æw. 3,
;gdzie dane tymczasowe przechowywane s¹ w sekcji danych programu (nie na stosie).
;Opracowany podprogram w³¹czyæ do kompletnego programu w asemblerze, 
;w którym podprogram bêdzie kilkakrotnie wywo³ywany dla ró¿nych wartoœci argumentów.

.686
.model flat
extern __write : PROC
extern _ExitProcess@4 : PROC

.data
; deklaracja tablicy 12-bajtowej do przechowywania
; tworzonych cyfr
dzielnik dd 1
znaki db 12 dup (?)

;w0 dd 0
;w1 dd 0
;w2 dd 0
.code

_wyswietl_EAX PROC
	push ebp
	mov ebp,esp  ; prolog
	
	sub esp,48  ; rezerwacja zmiennej lokalnych

	push esi
	push edi
	push ebx




	;mov w2,ecx
	lea ecx,[ebp-48]	; ustalenie adresu zmiennej lokalnej w
	mov eax,[ebp+8]	    ; przepisanie paramteru do zmiennej lokalnej
	mov [ecx],eax
	mov eax,[ebp+12]
	mov [ecx+4],eax

	lea edi,[ebp-40]
		
	mov esi, 38 ; indeks w tablicy 'znaki' 
	mov ebx, 10 ; dzielnik równy 10
konwersja: 
	mov edx, 0 ; zerowanie starszej czêœci dzielnej 
	
	;mov eax,w2
	;div ebx ; dzielenie przez 10, reszta w EDX, 
			; iloraz w EAX 
    ;mov w2,eax
	

	mov eax,[ecx+4]
	div ebx ; dzielenie przez 10, reszta w EDX, 
			; iloraz w EAX 
    mov [ecx+4],eax
	mov eax,[ecx]
	div ebx
	mov [ecx],eax

	add dl, 30H ; zamiana reszty z dzielenia na kod ASCII 
	mov [edi][esi], dl; zapisanie cyfry w kodzie ASCII
	dec esi ; zmniejszenie indeksu 
	
	or  eax, [ecx+4] ; sprawdzenie czy iloraz = 0 
	;or  eax,w2
	jnz konwersja ; skok, gdy iloraz niezerowy
; wype³nienie pozosta³ych bajtów spacjami i wpisanie 
; znaków nowego wiersza 
wypeln: 
	or esi, esi		; cmp esi,0
	jz wyswietl ; skok, gdy ESI = 0 
	mov byte PTR [edi][esi], 20H ; kod spacji 
	dec esi ; zmniejszenie indeksu 
	jmp wypeln 

wyswietl: 
	mov byte PTR [edi+0], 0AH ; kod nowego wiersza 
	mov byte PTR [edi][39], 0AH ; kod nowego wiersza
; wyœwietlenie cyfr na ekranie 
	push dword PTR 40 ; liczba wyœwietlanych znaków 
	;push dword PTR OFFSET znaki ; adres wyœw. obszaru 
	push edi
	push dword PTR 1; numer urz¹dzenia (ekran ma numer 1) 
	call __write ; wyœwietlenie liczby na ekranie 
	add esp, 12 ; usuniêcie parametrów ze stosu

	pop ebx
	pop edi
	pop esi
	
	add esp,48	; usuniêcie zmiennej dynamicznej
	pop ebp	
	ret
_wyswietl_EAX ENDP


main PROC
	;mov edx,1
	;mov eax,0
	;div dzielnik

	mov ecx,-1
	mov edx,0ffffffffh
	mov eax,0ffffffffh
	call _wyswietl_EAX
	push 0
	call _ExitProcess@4
main ENDP
END
