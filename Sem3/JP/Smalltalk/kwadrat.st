Object subclass: #Wielokat
	instanceVariableNames: 'wierzcholki nazwa '
	classVariableNames: ''
	poolDictionaries: ''
	category: 'JezykiProgramowania'!

!Wielokat methodsFor: 'initialize-release'!

initialize: liczbaWierzcholkow name: nowaNazwa
	"konstruktor obiektu - wielokata"

	nazwa:=nowaNazwa.
	wierzcholki:=Array new: liczbaWierzcholkow.
	wierzcholki at: 1 put: 0@0.! !

!Wielokat methodsFor: 'accessing'!

nazwa
	"podaje nazwe wielokata"

	^nazwa!

nazwa: nowa_nazwa
	"ustawia nowa nazwe wielokata"

	nazwa:=nowa_nazwa! !



Wielokat subclass: #Kwadrat
	instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'JezykiProgramowania'!


!Kwadrat methodsFor: 'arithmetic'!

+ figura
	"dodaj 2 figury w sensie pola"

	| p |

	p:=self pole + figura pole.
	^(Kwadrat new) initialize: p sqrt! !

!Kwadrat methodsFor: 'actions'!

pole
	"licz pole kwadratu"

	^(wierzcholki at: 2) x squared! !

!Kwadrat methodsFor: 'initialize-release'!

initialize: bok
	"tworz kwadrat o podanym boku"

	super initialize: 4 name: 'Kwadrat'.
	wierzcholki at: 2 put: bok@0.
	wierzcholki at: 3 put: bok@bok.
	wierzcholki at: 4 put: 0@bok.! !
	

Wielokat subclass: #Hexagon
    instanceVariableNames: ''
    classVariableNames: 'wspolczynnik my_bok'
    poolDictionaries: ''
    category: 'JezykiProgramowania'!

!Hexagon methodsFor: 'initialize-release'!

initialize: bok
	"tworz sześciokąt foremny o podanym boku"
	wspolczynnik := (3 * sqrt(3) / 2).
	my_bok := bok.

    super initialize: 6 name: 'Hexagon'.
    | angle radianAngle x y |
    
    angle := 60.  "Each internal angle in a regular hexagon is 60 degrees"
    radianAngle := (angle * Float pi / 180).  "Convert angle to radians"
    
    x := bok * (radianAngle cos).
    y := bok * (radianAngle sin).

	"Set up each vertex based on the side length and angles, placing them in a regular hexagon pattern"
    wierzcholki at: 2 put: x@y.
    wierzcholki at: 3 put: (x + bok)@y.
    wierzcholki at: 4 put: (x + x + bok)@0.
    wierzcholki at: 5 put: (x + bok)@(-y).
    wierzcholki at: 6 put: x@(-y).! !

!Hexagon methodsFor: 'arithmetic'!

+ figura
    "dodaj 2 figury w sensie pola"

    | p new_bok |

    p := self pole + figura pole.
	new_bok := p / wspolczynnik.
    ^(Hexagon new) initialize: new_bok sqrt! !

!Hexagon methodsFor: 'actions'!

pole
    "Licz pole sześciokątu"

    ^wspolczynnik * my_bok * my_bok! !




	
| myKwadrat area |
"Create a square with side length 5"
myKwadrat := Kwadrat new initialize: 5.

"Calculate the area of the square"
area := myKwadrat pole.

"Print the area"
area displayNl.


| myHexagon area1 |
"Create a square with side length 5"
myHexagon := Hexagon new initialize: 5.


"Calculate the area of the square"
area1 := myHexagon pole.

"Print the area"
area1 displayNl.
