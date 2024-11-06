LICZ=1
ps -f | while read LINIA;do
    echo "$LICZ. $LINIA"
    LICZ=$(($LICZ+1)) #ta zmienna jest w innym zakresie! pipeline przechodzi do innego procesu (innej powłoki)
done
echo $LICZ