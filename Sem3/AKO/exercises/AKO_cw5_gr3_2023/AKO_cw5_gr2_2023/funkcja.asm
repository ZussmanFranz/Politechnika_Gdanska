;Napisaæ podprogram w asemblerze ‘wyswietl_EAX’, 
;który wyœwietli na ekranie zawartoœæ rejestru ecx:edx:EAX w postaci liczby dziesiêtnej. 
;Zak³adamy, ¿e w rejestrach ecx:edx:EAX znajduje siê 96-bitowa liczba binarna bez znaku.
;Cyfry uzyskiwane w trakcie kolejnych dzieleñ nale¿y zapisywaæ w 12-bajtowym 
;obszarze pamiêci zarezerwowanym na stosie.
;Podprogram jest podobny do opisanego w instrukcji laboratoryjnej do æw. 3,
;gdzie dane tymczasowe przechowywane s¹ w sekcji danych programu (nie na stosie).
;Opracowany podprogram w³¹czyæ do kompletnego programu w asemblerze, 
;w którym podprogram bêdzie kilkakrotnie wywo³ywany dla ró¿nych wartoœci argumentów.

.686
.model flat
extern __write : PROC
extern _ExitProcess@4 : PROC

public _main
public _suma
public _wyswietl_EAX

.data
; deklaracja tablicy 12-bajtowej do przechowywania
; tworzonych cyfr
dzielnik dd 1
znaki db 12 dup (?)
w0 dd 0
w1 dd 0
.code

_suma PROC
	push ebp			; prolog
	mov ebp,esp  

	mov eax,[ebp+8]
	add eax,[ebp+12]
	
	pop ebp
	ret
_suma ENDP

_wyswietl_EAX PROC
	push ebp
	mov ebp,esp
	sub esp,24  ; rezerwacja zmiennej dynamicznej
	pushad
	mov w1,edx
	mov w0,eax
	;mov eax,[ebp+8]
	mov edi,esp
	;lea edi,[ebp-12]
		
	mov esi, 22 ; indeks w tablicy 'znaki' 
	mov ebx, 10 ; dzielnik równy 10
konwersja: 
	mov edx, 0 ; zerowanie starszej czêœci dzielnej 
	mov eax, w1
	div ebx ; dzielenie przez 10, reszta w EDX, 
			; iloraz w EAX 
    mov w1,eax

	; reszta r1 jest w edx
	mov eax,w0  ; a0 = w0
	div ebx
	mov w0,eax

	add dl, 30H ; zamiana reszty z dzielenia na kod ASCII 
	mov [edi][esi], dl; zapisanie cyfry w kodzie ASCII
	dec esi ; zmniejszenie indeksu 
	or eax,w1
	;cmp eax, 0 ; sprawdzenie czy iloraz = 0 
	jne konwersja ; skok, gdy iloraz niezerowy
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
	mov byte PTR [edi][23], 0AH ; kod nowego wiersza
; wyœwietlenie cyfr na ekranie 
	push dword PTR 24 ; liczba wyœwietlanych znaków 
	;push dword PTR OFFSET znaki ; adres wyœw. obszaru 
	push edi
	push dword PTR 1; numer urz¹dzenia (ekran ma numer 1) 
	call __write ; wyœwietlenie liczby na ekranie 
	add esp, 12 ; usuniêcie parametrów ze stosu

	
	popad
	add esp,24	; usuniêcie zmiennej dynamicznej
	pop ebp
	ret
_wyswietl_EAX ENDP


_main PROC
	;mov edx,1	 ; 0000 0010 0000 0000h
	;mov eax,0
	;div dzielnik

	mov edx,1
	mov eax,0
	call _wyswietl_EAX
	push 0
	call _ExitProcess@4
_main ENDP
END
