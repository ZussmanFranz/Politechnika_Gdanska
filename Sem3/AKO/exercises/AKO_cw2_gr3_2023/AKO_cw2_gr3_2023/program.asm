.686
.model flat

extern _ExitProcess@4 :proc
extern _MessageBoxA@16 : proc

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



.code
_main PROC
	
	push 4 ;4 - uType
	push OFFSET tytul
	push OFFSET tekst
	push 0 ;1 - HWND
	call _MessageBoxA@16

	push 5  ; kod powrotu
	call _ExitProcess@4

_main ENDP


END