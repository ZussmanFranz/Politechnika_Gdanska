.686
.model flat

public _dodaj_jeden

.code
_dodaj_jeden PROC
	push ebp
	mov ebp,esp
	push esi
	push edi
	push ebx

	mov eax,[ebp+8]  ;odczytanie argumentu >0
	shr eax,23		; w al wykladnik
	cmp al,127
	jae liczba_wieksza_od_1

	mov cl,127
	sub cl,al			 ; w cl ró¿nica wyk³adników pomiêdzy 1 a argumentem
	mov eax,[ebp+8]
	and eax,007fffffh	 ; wyzerowanie wykladnika
	bts eax,23			 ; ustawienie jawnej jedynki
	shr eax,cl
	
	mov ebx,127
	shl ebx,23			 ; pozycjonowanie wykladnika docelowego
	or eax,ebx			 ; w eax - wynikowa liczba
	jmp koniec

liczba_wieksza_od_1:
	mov cl,al
	sub cl,127			; obliczenie ró¿nicy wykladnikow

	mov ebx,0
	bts ebx,23			; zbudowanie mantysy 1.0000000000

	shr ebx,cl
	
	movzx ecx,al		; ustawienie oryginalnego wykladnika

	mov eax,[ebp+8]
	and eax,007FFFFFh	; uzyskanie mantysy (niejawnej) argumentu
	add eax,ebx			; suma mantys
	btr  eax,23
	jnc bez_korekcji
	shr eax,1
	add cl,1

bez_korekcji:
	shl ecx,23			; pozycjonowanie wykladnika
	or eax,ecx			; scalenie pola wykladnika i mantysy


koniec:
	push eax
	fld dword ptr [esp]
	add esp,4



	pop ebx
	pop edi
	pop esi
	pop ebp
	ret
_dodaj_jeden  ENDP

END