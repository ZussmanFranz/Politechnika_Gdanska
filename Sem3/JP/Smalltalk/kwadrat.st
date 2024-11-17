"Autorzy: Yauheni Pyryeu 201253
          Matsvei Kasparovich 201627
		  Anastazja Kniażewska 196629"

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
            Transcript show: 'Vertex ', index asString , ': ( ', wierzcholek x asString, ' , ', wierzcholek y asString, ' )'; cr
        ].
        Transcript show: 'Field: ', self area asString; cr.
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

        p := self area + figura area.
        ^(Kwadrat new) initialize: p sqrt
    !
!

!Kwadrat methodsFor: 'actions'!
    area
        "calculate the area of rectangle"

        ^(wierzcholki at: 2) x squared
    !

    circumscribe
        "circumscribe a circle around a Rectangle"

        | cent rad |

        cent := (wierzcholki at: 2) x / 2.
        rad := ((wierzcholki at: 2) x / 2) * 2 sqrt.
        Transcript cr; show: 'Circumscribe a figure: ', nazwa, ' by Circle '; cr.
        ^(Circle new) initialize: rad center: cent@cent
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

        p := self area + figura area.
        ^(Hexagon new) initialize: (4*p/((3 sqrt)*6)) sqrt
    !
!

!Hexagon methodsFor: 'actions'!
    area
        "calculate Hexagon's area"

        ^ 6 * ((wierzcholki at: 6) y squared)*(3 sqrt)/4
    !

    circumscribe
        "circumscribe a circle around the Hexagon"

        | cent rad |

        cent := ((wierzcholki at: 2) x)@ ((wierzcholki at: 2) y * -1).
        rad := (wierzcholki at: 6) y.
        Transcript cr; show: 'Circumscribe a figure: ', nazwa, ' by Circle '; cr.
        ^(Circle new) initialize: rad center: cent
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
        wierzcholki at: 2 put: ((3 sqrt) / 2 * bok)@(-1 * bok / 2).
        wierzcholki at: 3 put: ((3 sqrt) * bok)@0.
        wierzcholki at: 4 put: ((3 sqrt) * bok)@bok.
        wierzcholki at: 5 put: ((3 sqrt) / 2 * bok)@(bok * 1.5).
        wierzcholki at: 6 put: 0@bok.
    !
!


Object subclass: #Circle
	instanceVariableNames: 'center radius '
	classVariableNames: ''
	poolDictionaries: ''
	category: 'JezykiProgramowania'
!

!Circle methodsFor: 'initialize-release'!
    initialize: aRadius center: aPoint
        "Initialize a Circle with a given radius and center point.
        - aRadius: Integer representing the radius.
        - aPoint: Point representing the center of the circle."

        radius := aRadius.
        center := aPoint.
    !
!

!Circle methodsFor: 'accessing'!
    radius
        "gives radius of the circle"

        ^radius.
    !

    radius: new_radius
        "sets a new radius of the circle"

        radius:=new_radius.
    !

	center
        "gives center of the circle"

        ^center.
    !

    center: new_center
        "sets a new center of the circle"

        center:=new_center.
    !
!

!Circle methodsFor: 'actions'!
    print
        "prints circle data"

        Transcript cr; show: 'Figure: Circle'; cr.
		Transcript show: 'Center: ( ', center x asString, ' , ',  center y asString, ' )'; cr.
		Transcript show: 'Radius: ', radius asString; cr.
        Transcript show: 'Area: ', self area asString; cr.
    !

	area
        "Calculate and return the area of the circle."
        ^Float pi * (radius squared).
    !
!

"Testy:"


rect := (Kwadrat new) initialize: 2.
hex := (Hexagon new) initialize: 2.

Transcript show: 'Given Figures:'; cr.
hex print.
rect print.

Transcript cr; show: 'Circumscribe figures:'; cr.

new_circ_rect := rect circumscribe.
new_circ_rect print.

new_circ_hex := hex circumscribe.
new_circ_hex print.

rect1 := rect rescale: 0.5.
rect1 print.
new_circ_rect := rect1 circumscribe.
new_circ_rect print.

hex1 := hex rescale: 2.
hex1 print.
new_circ_hex := hex1 circumscribe.
new_circ_hex print.


Transcript cr; show: 'hex + rect'.
hex2 := hex + rect.
hex2 print.

Transcript cr; show: 'rect + hex'.
rect2 := rect + hex.
rect2 print.

Transcript show: 'Circle initialization:'; cr.
circ := (Circle new) initialize: 2 center: 0@0.
circ print.

