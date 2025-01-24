% Sortowanie szybkie (Quick Sort)

podziel_szybkie(_, [], [], []).
podziel_szybkie(Pivot, [H | T], Mniejsze, [H | WiekszeRowne]) :-
    H > Pivot,
    podziel_szybkie(Pivot, T, Mniejsze, WiekszeRowne).
podziel_szybkie(Pivot, [H | T], [H | Mniejsze], WiekszeRowne) :-
    H =< Pivot,
    podziel_szybkie(Pivot, T, Mniejsze, WiekszeRowne).

sortuj_szybkie([], []).
sortuj_szybkie([H | T], S) :-
    podziel_szybkie(H, T, Mniejsze, WiekszeRowne),
    sortuj_szybkie(Mniejsze, SMniejsze),
    sortuj_szybkie(WiekszeRowne, SWiekszeRowne),
    polacz(SWiekszeRowne, [H | SMniejsze], S).

polacz([],L,L).
polacz([H|T],L2,[H|Res]):- polacz(T,L2,Res).

% Predykat główny sortuj/2
sortuj(L, S) :-
    sortuj_szybkie(L, S).