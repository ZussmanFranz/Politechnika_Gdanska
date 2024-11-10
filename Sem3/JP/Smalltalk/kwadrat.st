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
    classVariableNames: ''
    poolDictionaries: ''
    category: 'JezykiProgramowania'!

!Hexagon methodsFor: 'initialize-release'!

initialize: bok
    "Initialize a regular hexagon with a specified side length"

    super initialize: 6 name: 'Hexagon'.
    | angle radianAngle x y |
    
    angle := 60.  "Each internal angle in a regular hexagon is 60 degrees"
    radianAngle := (angle * Float pi / 180).  "Convert angle to radians"
    
    "Set up each vertex based on the side length and angles, placing them in a regular hexagon pattern"
    wierzcholki at: 1 put: bok@0.
    x := bok * (cos radianAngle).
    y := bok * (sin radianAngle).
    wierzcholki at: 2 put: x@y.
    wierzcholki at: 3 put: (2 * x)@0.
    wierzcholki at: 4 put: (2 * x)@(-y).
    wierzcholki at: 5 put: x@(-2 * y).
    wierzcholki at: 6 put: 0@(-y).! !

!Hexagon methodsFor: 'arithmetic'!

+ figura
    "Add two figures in terms of area"

    | p |

    p := self pole + figura pole.
    ^(Hexagon new) initialize: (p / (3 * sqrt(3) / 2)) sqrt! !

!Hexagon methodsFor: 'actions'!

pole
    "Calculate the area of the hexagon"

    ^(3 * sqrt(3) / 2) * ((wierzcholki at: 1) x squared)! !
