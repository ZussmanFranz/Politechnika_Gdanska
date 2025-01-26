% Autorzy: 201253 196629 201627
% 3. sortowanie przez wybieranie (selection Sort)

usun_max([X], X, []).
usun_max([H | T], M, [H | R]) :-
    usun_max(T, M1, R),
    H =< M1,
    M is M1.
usun_max([H | T], M, [M1 | R]) :-
    usun_max(T, M1, R),
    H > M1,
    M is H.

sortuj_wybieranie([], []).
sortuj_wybieranie(L, [M | S]) :-
    usun_max(L, M, R),
    sortuj_wybieranie(R, S).

% Predykat główny sortuj/2
sortuj(L, S) :-
    sortuj_wybieranie(L, S).