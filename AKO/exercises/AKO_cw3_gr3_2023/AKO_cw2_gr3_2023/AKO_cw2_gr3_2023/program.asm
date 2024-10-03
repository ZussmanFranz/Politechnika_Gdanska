.686
.model flat

extern _ExitProcess@4 :proc
extern _MessageBoxW@16 : proc

public _main


.data
tekst	db 41h
	db 6Bh
	db 6fh
	db 0
	dw 41h,6bh,6fh
	dw 'A','k','o'
a	dw 'Ak','o'
	;dw 'Ako'

tytul 	db 'Ako',0
bufor	db	50H, 6FH, 0C5H, 82H, 0C4H, 85H, 63H, 7AH, 65H, 6EH, 69H, 61H, 20H
		db	0F0H, 9FH, 9AH, 82H   ; parowoz
		db	20H, 20H, 6BH, 6FH, 6CH, 65H, 6AH, 6FH, 77H, 6FH, 20H
		db	0E2H, 80H, 93H ; polpauza
		db	20H, 61H, 75H, 74H, 6FH, 62H, 75H, 73H, 6FH, 77H, 65H, 20H, 20H
		db	0F0H,  9FH,  9AH,  8CH ; autobus 

wynik   dw  48 dup (0)


		;db  50h,0, 6fh, 00h,42h,1
		;dw   50h, 006fh,142h


.code
_main PROC
	
	mov ecx,offset wynik - offset bufor
	mov esi,0
	mov edi,0


et:
	mov al,bufor[esi]
	add esi,1
	cmp al,7fh
	ja znak_uft8_wielobajtowy
	mov ah,0
	mov wynik[edi],ax
	add edi,2

znak_uft8_wielobajtowy:
	loop et

	push 4 ;4 - uType
	push OFFSET tytul
	push OFFSET wynik
	push 0 ;1 - HWND
	call _MessageBoxW@16

	push 5  ; kod powrotu
	call _ExitProcess@4

_main ENDP


END