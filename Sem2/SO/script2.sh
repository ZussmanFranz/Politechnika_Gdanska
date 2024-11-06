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

while [ true ]
do
echo "1)Nazwa: ${Nazwa}"
echo "2)Katalog: ${Katalog}"
echo "3)Rozszerzenie: ${Rozszerzenie}"
echo "4)Edytuj zawartość"
echo "5)Filtruj zawartość względem:  ${Filtr}"
if [ "$Rozmiar" != "" ]; then
    echo "6)Rozmiar pliku: ${Rozmiar} B"
else
    echo "6)Rozmiar pliku: ${Rozmiar}"
fi

echo "7)Data modyfikacji:  ${ModDate}"
echo "8)Data utworzenia:  ${CreateDate}"
echo "9)Wyświetl zawartość"
echo "10)Szukaj"
echo "11)Koniec"

read Wybor

case "$Wybor" in
   "1") read -p "Wpisz nazwę: " Nazwa 
   ;;
   "2")	read -p "Wpisz katalog: " Katalog
   ;;
   "3") read -p "Wpisz rozszerzenie: " Rozszerzenie
	Rozszerzenie=".$Rozszerzenie"
   ;;
   "4")find $Katalog -name $Nazwa$Rozszerzenie -exec nano {} \;
   ;; 
   "5") read -p "Wpisz filtr: " Filtr 
   ;;
   "6")Rozmiar=$(find $Katalog -name $Nazwa$Rozszerzenie -exec stat --format='%s' {} \;)
   ;;
   "7")ModDate=$(find $Katalog -name $Nazwa$Rozszerzenie -exec stat --format='%y' {} \;)
   ;;
   "8")CreateDate=$(find $Katalog -name $Nazwa$Rozszerzenie -exec stat --format='%w' {} \;)
   ;;
   "9")	echo "--------"
   if [[ $Filtr = "" ]]
   then
   find $Katalog -name $Nazwa$Rozszerzenie -exec cat {} \;
   else
   find $Katalog -name $Nazwa$Rozszerzenie -exec cat {} \; | grep $Filtr
   fi
   echo "--------"
   ;;
   "10") echo "--------"
	find $Katalog -name $Nazwa$Rozszerzenie
	echo "--------"
   ;;
   "11") exit 0
   ;;
esac
done


