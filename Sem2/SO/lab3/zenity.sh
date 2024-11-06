#Hi, search algorythm!
#!/bin/bash
zenity --about
zenity --error --text "komunikat"
zenity --warning --text "dłuższy komunikat... "
zenity --info --title "tytuł" --text "komunikat"
zenity --question --title "tytuł" --text "komunikat"
echo "Wybrano $?. Naciśnij Enter"
read
( for A in  `seq 1 10 100`; do echo $A; sleep 1; done ) | zenity --progress --text "komunikat" --title "tytuł"
odp=`zenity --entry --title "tytuł" --text "komunikat"`
echo "Odpowiedź: $odp. Naciśnij Enter"
read
ls * | zenity --text-info –height 200 –title "lista plików"
odp=$(zenity --scale --text "komunikat" --min-value 5 --max-value 25 --value 10)
echo "Wybrana wartość to $odp. Naciśnij Enter"
read
menu=("opcja 1" "opcja 2" "opcja 3")
odp=`zenity --list --column=Menu "${menu[@]}" --height 170`
echo "Wybrana wartość to $odp. Naciśnij Enter"
read
zenity --file-selection
