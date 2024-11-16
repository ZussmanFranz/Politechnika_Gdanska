"Autorzy: Yauheni Pyryeu 201253
          Matsvei Kasparovich 201627
		  Настя"

Object subclass: #Wielokat
	instanceVariableNames: 'wierzcholki nazwa '
	classVariableNames: ''
	poolDictionaries: ''
	category: 'JezykiProgramowania'
!

!Wielokat methodsFor: 'initialize-release'!
    initialize: liczbaWierzcholkow name: nowaNazwa
        "konstruktor obiektu - wielokata"

        nazwa := nowaNazwa.
        wierzcholki := Array new: liczbaWierzcholkow.
        wierzcholki at: 1 put: 0@0.
    !
!

!Wielokat methodsFor: 'accessing'!
    nazwa
        "podaje nazwe wielokata"

        ^nazwa
    !

    nazwa: nowa_nazwa
        "ustawia nowa nazwe wielokata"

        nazwa:=nowa_nazwa
    !
!

!Wielokat methodsFor: 'actions'!
    print
        "prints wielokat data"

        Transcript cr; show: 'Figure: ', nazwa; cr.
        wierzcholki keysAndValuesDo: [ :index :wierzcholek |
            Transcript show: 'Vertex ', index asString , ': (', Character tab asString, wierzcholek x asString, ' , ', wierzcholek y asString, ' )'; cr
        ].
        Transcript show: 'Field: ', self pole asString; cr.
    !
!


Wielokat subclass: #Kwadrat
	instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'JezykiProgramowania'
!

!Kwadrat methodsFor: 'arithmetic'!
    + figura
        "dodaj 2 figury w sensie pola"

        | p |

        p := self pole + figura pole.
        ^(Kwadrat new) initialize: p sqrt
    !
!

!Kwadrat methodsFor: 'actions'!
    pole
        "licz pole kwadratu"

        ^(wierzcholki at: 2) x squared
    !
!

!Kwadrat methodsFor: 'modifiers'!
    rescale: scale
        "Rescale figure' side by scale"

        | bok |
        Transcript cr; show: 'Rescale side of figure : ', nazwa, ' by scale ', scale asString.
        bok := (wierzcholki at: 2) x.
        ^(Kwadrat new) initialize: bok * scale
    !
!

!Kwadrat methodsFor: 'initialize-release'!
    initialize: bok
        "tworz kwadrat o podanym boku"

        super initialize: 4 name: 'Kwadrat'.
        wierzcholki at: 2 put: bok@0.
        wierzcholki at: 3 put: bok@bok.
        wierzcholki at: 4 put: 0@bok.
    !
!


Wielokat subclass: #Hexagon
    instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'JezykiProgramowania'
!

!Hexagon methodsFor: 'arithmetic'!
    + figura
        "dodaj 2 figury w sensie pola"

        | p |

        p := self pole + figura pole.
        ^(Hexagon new) initialize: (4*p/((3 sqrt)*6)) sqrt
    !
!

!Hexagon methodsFor: 'actions'!
    pole
        "calculate Hexagon's field"

        ^ 6 * ((wierzcholki at: 6) y squared)*(3 sqrt)/4
    !
!

!Hexagon methodsFor: 'modifiers'!
    rescale: scale
        "Rescale figure' side by scale"

        | bok |
        Transcript cr; show: 'Rescale side of figure : ', nazwa, ' by scale ', scale asString.
        bok := (wierzcholki at: 6) y.
        ^(Hexagon new) initialize: bok * scale
    !
!

!Hexagon methodsFor: 'initialize-release'!
    initialize: bok
        "create regular Hexagon with given side length"
        super initialize: 6 name: 'Hexagon'.
        wierzcholki at: 2 put: ((3 sqrt) / 2 * bok)@(bok / 2).
        wierzcholki at: 3 put: ((3 sqrt) * bok)@0.
        wierzcholki at: 4 put: ((3 sqrt) * bok)@bok.
        wierzcholki at: 5 put: ((3 sqrt) / 2 * bok)@(bok * 1.5).
        wierzcholki at: 6 put: 0@bok.
    !
!


" Object subclass: #Circle
	instanceVariableNames: 'center radius '
	classVariableNames: ''
	poolDictionaries: ''
	category: 'JezykiProgramowania'
! "


rect := (Kwadrat new) initialize: 2.
hex := (Hexagon new) initialize: 2.

Transcript show: 'Given Figures:'; cr.
hex print.
rect print.

Transcript cr; show: 'hex + rect'.
hex1 := hex + rect.
hex1 print.

Transcript cr; show: 'rect + hex'.
rect1 := rect + hex.
rect1 print.


hex3 := hex rescale: 2.
hex3 print.
rect3 := rect rescale: 0.5.
rect3 print.