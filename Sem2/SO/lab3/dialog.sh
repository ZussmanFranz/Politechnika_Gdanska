WARTOSC=`dialog --stdout --title "Test dialog" --backtitle "Dzialanie programu dialog w przykladach..." --msgbox "msgbox\nmsgbox" 8 60 `
echo $?
echo $WARTOSC
read

WARTOSC=`dialog --stdout --title "Test dialog" --backtitle "Dzialanie programu dialog w przykladach..." --infobox "infobox\n  infobox" 8 60 `
echo $?
echo $WARTOSC
read

WARTOSC=`dialog --stdout --title "Test dialog" --backtitle "Dzialanie programu dialog w przykladach..." --inputbox "inputbox" 8 60 `
echo $?
echo $WARTOSC
read

WARTOSC=`dialog --stdout --title "Test dialog" --backtitle "Dzialanie programu dialog w przykladach..."  --yesno "yesno" 8 60 `
echo $?
echo $WARTOSC
read

WARTOSC=`dialog --stdout --title "Test dialog" --backtitle "Dzialanie programu dialog w przykladach..."  --menu "menu" 10 60 5 "1" "tekst" "2" "tekst2" `
echo $?
echo $WARTOSC
read

WARTOSC=`dialog --stdout --title "Test dialog" --backtitle "Dzialanie programu dialog w przykladach..." --checklist "checklist" 10 60 5 "1" "tekst" on "2" "tekst2" off `
echo $?
echo $WARTOSC
read

WARTOSC=`dialog --stdout --title "Test dialog" --backtitle "Dzialanie programu dialog w przykladach..." --radiolist "Radio List" 15 60 5 "1" "tekst" on "2" "tekst2" off `
echo $?
echo $WARTOSC
read

( for A in `seq 100`; do
echo $A
sleep 1
done )|dialog --stdout --title "Test dialog" --backtitle "Dzialanie programu dialog w przykladach..." --gauge "gauge" 15 60 5 

echo $?
read


