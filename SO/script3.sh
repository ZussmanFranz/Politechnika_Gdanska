#!/bin/bash
# 1)Nazwa
# 2)Katalog
# 3)Rozszerzenie
# 4)Edytuj zawartość
# 5)Filtruj zawartość
# 6)Rozmiar pliku
# 7)Data modyfikacji
# 8)Data utworzenia
# 9)Wyświetl zawartość
# 10)Szukaj
# 11)Koniec

while getopts hned: OPT; do
    case ${OPT} in
        h) help
        ;;
        n) Nazwa=${OPTARG}
        ;;
        e) Rozszerzenie=${OPTARG}
        ;;
        d) Katalog=${OPTARG}
        ;;
    esac
done

while [ true ]
do
menu=("Nazwa: ${Nazwa}" "Katalog: ${Katalog}" "Rozszerzenie: ${Rozszerzenie}" "Edytuj zawartość" "Filtruj zawartość: ${Filtr}" "Rozmiar pliku:  ${Rozmiar}" "Data modyfikacji:  ${ModDate}" "Data utworzenia:  ${CreateDate}" "Wyświetl zawartość" "Szukaj" "Koniec")
# wyświetlenie menu głównego
opt=$(zenity --list --height 640 --title="script 3" --text="Rozbudowana, inteligentna i wspaniała wyszukiwarka plików" --cancel-label "Wyjdź" --ok-label "Wybierz opcję" --column="Menu główne" "${menu[@]}")

if [[ $? -eq 1 ]]; then
   exit 0
fi

case "$opt" in
    "${menu[0]}")
        #read -p "Wpisz nazwę: " Nazwa
        Nazwa=$(zenity --entry --title "Nazwa" --text "Wpisz nazwę:"  --height 120) 
        ;;
    "${menu[1]}")
        #read -p "Wpisz katalog: " Katalog
        Katalog=$(zenity --entry --title "Katalog" --text "Wpisz katalog:"  --height 120) 
        ;;
    "${menu[2]}")
        #read -p "Wpisz rozszerzenie: " Rozszerzenie
        Rozszerzenie=$(zenity --entry --title "Rozszerzenie" --text "Wpisz rozszerznie:"  --height 120) 
        Rozszerzenie=".$Rozszerzenie"
        ;;
    "${menu[3]}")
        find $Katalog -name ${Nazwa}${Rozszerzenie} -exec nano {} \;
        ;;
    "${menu[4]}")
        Filtr=$(zenity --entry --title "Filtr" --text "Wpisz filtr:"  --height 120)  
        ;;
    "${menu[5]}")
        Rozmiar=$(find $Katalog -name $Nazwa$Rozszerzenie -exec stat --format='%s' {} \;)
        zenity --info --title="Rozmiar pliku" --text="$Rozmiar B" --width=300
        ;;
    "${menu[6]}")
        ModDate=$(find $Katalog -name $Nazwa$Rozszerzenie -exec stat --format='%y' {} \;)
        zenity --info --title="Data Modyfikacji" --text="$ModDate" --width=300
        ;;
    "${menu[7]}")
        CreateDate=$(find $Katalog -name $Nazwa$Rozszerzenie -exec stat --format='%w' {} \;)
        zenity --info --title="Data Utworzenia" --text="$CreateDate" --width=300
        ;;        
    "${menu[8]}")
        #echo "--------"
        if [[ $Filtr = "" ]]
        then
            Wynik=$(find $Katalog -name ${Nazwa}${Rozszerzenie} -exec cat {} \;)
        else
            Wynik=$(find $Katalog -name ${Nazwa}${Rozszerzenie} -exec cat {} \; | grep $Filtr)
        fi
        #echo "--------"

        zenity --list --height 360 --title "Filter" --text "" --column="Wynik" "${Wynik}"
        ;;
    "${menu[9]}")
        #echo "--------"
        #find $Katalog -name ${Nazwa}${Rozszerzenie}
        #echo "--------"
        Wynik=$(find $Katalog -name ${Nazwa}${Rozszerzenie})
        zenity --list --height 360 --title "Find" --text "" --column="Wynik" "${Wynik}"
        ;;
    "${menu[10]}")
        exit 0
        ;;
esac


done


