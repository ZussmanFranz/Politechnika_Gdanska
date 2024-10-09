#!/bin/bash

# autor: Krzysztof Czarnecki
# email: krzycz@eti.pg.gda.pl
#
# Politechnika Gdańska 
# Wydział Elektroniki, Telekomunikacji i Informatyki
# Katedra Systemów Elektroniki Morskiej
#
# Skrypt jest pomocą naukową dla przedmiotu systemy operacyjne.

gra="OSpolis"
zenity --info --title $gra --text "\nOSpolis jest grą ekonomiczną.\n\nGracz jest administratorem średniowiecznego miasta.\nJego zadaniem jest rozwój infrastruktury oraz zwiększenie liczby mieszkańców.\n\nGracz może zatrudniać ludzi do 3 zawodów: rolnicy, rzemieślnicy i naukowcy,\nmoże pobierać podatki oraz budować: domy - zwiększając pojemność miasta,\nbudować infrastrukturę rolniczą, naukową i przemysłową - zwiększając wydajność pracowników.\n\nGracz ma obowiązek zapewnić wyżywienie dla populacji miasta.\nWysokość podatków wpływa na pojemność miasta odwrotnie proporcjonalnie.\nPopulacja miasta rośnie proporcjonalnie do iloczynu liczby mieszkańców i wolnego miejsca.\nZgromadzone złoto podlega inflacji i malwersacji w wysokości 10% na turę.\nZgromadzona żywność podlega zepsuciu w wysokości 20% na turę.\nZgromadzony budulec podlega malwersacji w wysokości 5% na turę.\n\nPoczątkowa populacja to 100 osób.\nPowieszchnia miasta jest ustalana na początku gry.\nNa każdej jednostce powieszchni można wybudować tylko jeden budynek.\nWynikiem gracza jest ilość zgromadzonego złota na końcu gry."

# funkcja generuje tekst i umieszcza go w zmiennej $informacja
function generuj_panel_informacyjny(){
    case "$1" in
	"glowny" ) 
	    informacja="zarządca:$imie\nrok:$rok\n\nareał:$powieszchnia\npodatki:$tax%\nbudynki:$budynki\npopulacja:$people  [<span color=\"blue\">$delta_people</span>]\n"
	    informacja="$informacja\nzłoto:$gold  [<span color=\"blue\">$delta_gold</span>]\nbudulec:$build  [<span color=\"blue\">$delta_build</span>]\nżywność:$food  [<span color=\"blue\">$delta_food</span>]\n";;
	
	"zatrudnienie" ) informacja="populacja:$people\n\nbezrobotni:$niezatrudnieni\n\nrolnicy:$farm_employed\nrzemieślnicy:$manuf_employed\nnaukowcy:$lab_employed\n";;
	"zabudowa" ) informacja="areał:$powieszchnia\n\nzłoto:$gold\nbudulec:$build\nnieużytki:$miejsce\n\ndomy:$homes\nfarmy:$farms\nwarsztaty:$manufs\nszkoły:$labs\n";;
	*) echo "wrong argumnt";;
    esac
}

# opcje menu
menu=("Zarządzaj zatrudnieniem" "Zarządzaj zabudową" "Zmień stopę podatkową" "Koniec gry")
menu_zatrudnienie=("+ Zatrudnij rolników" "+ Zatrudnij rzemieślników" "+ Zatrudnij naukowców" "_ Zwolnij rolników" "_ Zwolnij rzemieślników" "_ Zwolnij naukowców")
menu_zabudowa=("+ Zbuduj domy" "+ Zbuduj farmy" "+ Zbuduj warsztaty" "+ Zbuduj szkoły" "_ Zburz domy" "_ Zburz farmy" "_ Zburz warsztaty" "_ Zburz szkoły")

# wczytywanie imienia gracza
imie=$(zenity --entry --title $gra --text "Podaj swoje imię:"  --height 120)
if test -z $imie 
then
    zenity --error --text "Nie zaakceptowano pustego imienia."
    exit
fi

# wczytywanie powieszchni miasta
powieszchnia=$(zenity --entry --title $gra --text "Podaj powieszchnię miasta (100 - 1 000 000, int):")
printf "%d" "$powieszchnia" &> /dev/null
if [[ $? -ne 0 ]] ; then
    echo "$powieszchnia is not a number."
    zenity --error --text "Nie zaakceptowano wyrażenia nienumerycznego."
    exit
fi
if [[ $powieszchnia -lt 100 || $powieszchnia -gt 1000000 ]];
then
    zenity --error --text "Wpisana wartość nie mieści się w wymaganym przedziale."
    exit
fi

# inicjacja zmiennych reprezentujących:
# zasoby
people=100
gold=100
food=100
build=100

# strukturę zatrudnienia
manuf_employed=0
farm_employed=0
lab_employed=0

# strukturę zabudowy
homes=0
manufs=0
farms=0
labs=0

# wielkość pobieranych podatków (0 - 1) i rok
tax=50
rok=1000

# cena budynku
cena_budynku_gold=10
cena_budynku_build=20

# zmiana zasobów z tury na turę
delta_people=0
delta_gold=0
delta_food=0
delta_build=0

# pętla główna
while true; do
    # pętla w ramach menu głównego
    while true; do    
	budynki=$(($homes+$manufs+$farms+$labs))    	

	# wyświetlenie menu głównego
	generuj_panel_informacyjny "glowny"
	opt=$(zenity --list --height 360 --title=$gra --text="$informacja" --cancel-label "Koniec tury" --ok-label "Wybierz opcję" --column="Menu główne" "${menu[@]}")
	if [[ $? -eq 1 ]]; then
	    echo "koniec tury"
	    break
	fi

	# obsługa menu głównego
	case "$opt" in
	    # podmenu zatrudnienie
	    "${menu[0]}" ) 
		while true; do

		    zatrudnieni=$(($manuf_employed+$farm_employed+$lab_employed))
		    # echo "Liczba ludzi pracujących: $zatrudnieni"

		    niezatrudnieni=$(($people-$zatrudnieni))
		    # echo "Liczba ludzi bez pracy: $niezatrudnieni"
		    
		    generuj_panel_informacyjny "zatrudnienie"
		    opt_zatrudnienie=$(zenity --list --height 340 --title=$gra --text="$informacja" --cancel-label "Menu główne" --ok-label "Wybierz opcję" --column="Menu zatrudnienie" "${menu_zatrudnienie[@]}")
		    if [[ $? -eq 1 ]]; then
			echo "menu główne"
			break
		    fi

		    	# obsługa podmenu zatrudnienie
		    case "$opt_zatrudnienie" in
			"${menu_zatrudnienie[0]}" ) 
			    staff=$(zenity --scale --text "Zatrudnij rolników" --value 0 --step 1 --min-value 0 --max-value $niezatrudnieni)
			    if [[ -z $staff ]]; then staff=0; fi
			    farm_employed=$(($farm_employed+$staff))
			    ;;
			"${menu_zatrudnienie[1]}" ) 
			    staff=$(zenity --scale --text "Zatrudnij rzemieślników" --value 0 --step 1 --min-value 0 --max-value $niezatrudnieni)
			    if [[ -z $staff ]]; then staff=0; fi
			    manuf_employed=$(($manuf_employed+$staff))
			    ;;
			"${menu_zatrudnienie[2]}" ) 
			    staff=$(zenity --scale --text "Zatrudnij naukowców" --value 0 --step 1 --min-value 0 --max-value $niezatrudnieni)
			    if [[ -z $staff ]]; then staff=0; fi
			    lab_employed=$(($lab_employed+$staff))
			    ;;
			"${menu_zatrudnienie[3]}" ) 
			    staff=$(zenity --scale --text "Zwolnij rolników" --value 0 --step 1 --min-value 0 --max-value $farm_employed)	   
			    if [[ -z $staff ]]; then staff=0; fi
			    farm_employed=$(($farm_employed-$staff))
			    ;;
			"${menu_zatrudnienie[4]}" ) 
			    staff=$(zenity --scale --text "Zwolnij rzemieślników" --value 0 --step 1 --min-value 0 --max-value $manuf_employed)
			    if [[ -z $staff ]]; then staff=0; fi
			    manuf_employed=$(($manuf_employed-$staff))
			    ;;
			"${menu_zatrudnienie[5]}" ) 
			    staff=$(zenity --scale --text "Zwolnij naukowców" --value 0 --step 1 --min-value 0 --max-value $lab_employed)
			    if [[ -z $staff ]]; then staff=0; fi
			    lab_employed=$(($lab_employed-$staff))
			    ;;
			*) echo "no marked";;
		    esac
		done
		;;
	    
	    # podmenu zabudowa
	    "${menu[1]}" ) 
		while true; do

		    budynki=$(($homes+$manufs+$farms+$labs))
		    echo "Liczba budynków: $budynki"

		    miejsce=$(($powieszchnia-$budynki))
		    echo "Obszar niezabudowany: $miejsce"
		    minimum=$miejsce

		    sztuk_gold=$(echo "$gold/$cena_budynku_gold" | bc)
		    if [[ $minimum -gt $sztuk_gold ]]; then
			minimum=$sztuk_gold
		    fi

		    sztuk_build=$(echo "$build/$cena_budynku_build" | bc)
		    if [[ $minimum -gt $sztuk_build ]]; then
			minimum=$sztuk_build
		    fi  # można zbudować $minimum budynków
		    
		    generuj_panel_informacyjny "zabudowa"
		    opt_zabudowa=$(zenity --list --height 430 --title=$gra --text="$informacja" --cancel-label "Menu główne" --ok-label "Wybierz opcję" --column="Menu zabudowa" "${menu_zabudowa[@]}")
		    if [[ $? -eq 1 ]]; then
			echo "menu główne"
			break
		    fi

		    # obsługa podmenu zabudowa
		    case "$opt_zabudowa" in
			"${menu_zabudowa[0]}" ) 			    
			    building=$(zenity --scale --text "Zbuduj domy" --value 0 --step 1 --min-value 0 --max-value $minimum)
			    if [[ -z $building ]]; then building=0; fi
			    homes=$(($homes+$building))
			    gold=$(($gold-$building*$cena_budynku_gold))
			    build=$(($build-$building*$cena_budynku_build))
			    ;;
			"${menu_zabudowa[1]}" ) 
			    building=$(zenity --scale --text "Zbuduj farmy" --value 0 --step 1 --min-value 0 --max-value $minimum)
			    if [[ -z $building ]]; then building=0; fi
			    farms=$(($farms+$building))
			    gold=$(($gold-$building*$cena_budynku_gold))
			    build=$(($build-$building*$cena_budynku_build))
			    ;;
			"${menu_zabudowa[2]}" ) 
			    building=$(zenity --scale --text "Zbuduj warsztaty" --value 0 --step 1 --min-value 0 --max-value $minimum)
			    if [[ -z $building ]]; then building=0; fi
			    manufs=$(($manufs+$building))
			    gold=$(($gold-$building*$cena_budynku_gold))
			    build=$(($build-$building*$cena_budynku_build))
			    ;;
			"${menu_zabudowa[3]}" ) 
			    building=$(zenity --scale --text "Zbuduj szkoły" --value 0 --step 1 --min-value 0 --max-value $minimum)
			    if [[ -z $building ]]; then building=0; fi
			    labs=$(($labs+$building))
			    gold=$(($gold-$building*$cena_budynku_gold))
			    build=$(($build-$building*$cena_budynku_build))
			    ;;
			"${menu_zabudowa[4]}" ) 			    
			    building=$(zenity --scale --text "Zburz domy" --value 0 --step 1 --min-value 0 --max-value $homes)
			    if [[ -z $building ]]; then building=0; fi
			    homes=$(($homes-$building))
			    ;;
			"${menu_zabudowa[5]}" ) 
			    building=$(zenity --scale --text "Zburz farmy" --value 0 --step 1 --min-value 0 --max-value $farms)
			    if [[ -z $building ]]; then building=0; fi
			    farms=$(($farms-$building))
			    ;;
			"${menu_zabudowa[6]}" ) 
			    building=$(zenity --scale --text "Zburz warsztaty" --value 0 --step 1 --min-value 0 --max-value $manufs)
			    if [[ -z $building ]]; then building=0; fi
			    manufs=$(($manufs-$building))
			    ;;
			"${menu_zabudowa[7]}" ) 
			    building=$(zenity --scale --text "Zburz szkoły" --value 0 --step 1 --min-value 0 --max-value $labs)
			    if [[ -z $building ]]; then building=0; fi
			    labs=$(($labs-$building))
			    ;;
			*) echo "no marked";;
		    esac
		done
		;;

	    # można zmienić stopę płaconych podatków
	    "${menu[2]}" ) 
		new_tax=$(zenity --scale --text "Ustaw stopę podatkową (%)" --value $tax --step 1 --min-value 0 --max-value 100)
		if [[ -z $new_tax ]]; then new_tax=$tax; fi
		tax=$new_tax
		;;
	    # zakończenie gry i zapisanie wyników do pliku rezultat.txt
	    "${menu[3]}" ) 
		result="zarządca:$imie\nareał:$powieszchnia\nrok:$rok\nzłoto:$gold"
		zenity --question --text="Napewno chcesz zakończyć grę?\n$result"
		if [[ $? -eq 0 ]]; then
		    result="zarządca:$imie areał:$powieszchnia rok:$rok złoto:$gold"
		    echo $result >> rezultat.txt
		    exit
		fi
		;;
	    *) echo "no marked";;
	esac	
    done    


    # przeliczenia prowadzone na końcu tury:

    # dzięki wiedzy pracownicy są bardziej efektywni
    knowledge=$(echo "10*$lab_employed*(1+$labs/($labs+$powieszchnia))" | bc -l)

    # aktualizacja żywności
    delta_food=$(echo "0.2*$food" | bc -l)
    delta_food=$(echo "3*$farm_employed*(1+$knowledge/($knowledge+$powieszchnia))*(1+$farms/($farms+$powieszchnia)) - $people - $delta_food" | bc -l)
    delta_food=${delta_food%.*}
    food=$(($food+$delta_food))
    # echo "delta food: $delta_food"

    # aktualizacja budulca
    delta_build=$(echo "0.05*$build" | bc -l)
    delta_build=$(echo "$manuf_employed*(1+$knowledge/($knowledge+$powieszchnia))*(1+$manufs/($manufs+$powieszchnia)) - $delta_build" | bc -l)
    delta_build=${delta_build%.*}
    if [[ -z $delta_build || $delta_build = "-" ]]; then delta_build=0; fi
    build=$(($build+$delta_build))
    # echo "delta build: $delta_build"

    # aktualizacja złota
    delta_gold=$(echo "0.1*$gold" | bc -l)
    zatrudnieni=$(($manuf_employed+$farm_employed+$lab_employed))
    delta_gold=$(echo "$zatrudnieni*$tax/100 - $delta_gold" | bc -l)
    delta_gold=${delta_gold%.*}
    if [[ -z $delta_gold || $delta_gold = "-" ]]; then delta_gold=0; fi
    gold=$(($gold+$delta_gold))
    # echo "delta gold: $delta_gold"
    
    # brak żywności to problemy ze wzrostem liczby ludności
    if [[ $food -lt 0 ]]; then
	delta_people=$food
	delta_food=$(($delta_food-$food))
	food=0
    fi
    
    # przyrost ludności zależy m.in. od aktualnej pojemności miasta
    pojemnosc=$(echo "($powieszchnia + 10 * $homes) * (100-$tax)/100" | bc -l)
    delta_people2=$(echo "($pojemnosc-$people)/2" | bc -l)
    delta_people2=${delta_people2%.*}

    if [[ $delta_people2 -gt 0 ]]; then
	delta_people2=$(echo "sqrt($people*$delta_people2)" | bc -l)
    fi

    delta_people=$(echo "$delta_people+$delta_people2" | bc -l)
    delta_people=${delta_people%.*}
    if [[ -z $delta_people || $delta_people = "-" ]]; then delta_people=0; fi
    #echo $niezatrudnieni $manuf_employed $farm_employed $lab_employed

    if [[ $delta_people -ge 0 ]]; then
	people=$(($people+$delta_people))
    else
	# jeśli następuje spadek liczby ludności to należy zredukować również część zatrudnionych osób
	echo "Spadek liczby ludności!"
	factor=$(echo "1.0$delta_people.0/$people.0" | bc -l)
	zatrudnieni=$(($manuf_employed+$farm_employed+$lab_employed))
	niezatrudnieni=$(($people-$zatrudnieni))

	niezatrudnieni=$(echo "$factor*$niezatrudnieni" | bc -l)
	niezatrudnieni=${niezatrudnieni%.*}

	manuf_employed=$(echo "$factor*$manuf_employed" | bc -l)
	manuf_employed=${manuf_employed%.*}

	farm_employed=$(echo "$factor*$farm_employed" | bc -l)
	farm_employed=${farm_employed%.*}

	lab_employed=$(echo "$factor*$lab_employed" | bc -l)
	lab_employed=${lab_employed%.*}

	people_tmp=$(($niezatrudnieni+$manuf_employed+$farm_employed+$lab_employed))
	delta_people=$(($people_tmp-$people))
	people=$people_tmp
    fi

    # inkrementacja roku
    rok=$(($rok+1))
    # można narzucić rok końca gry
done
