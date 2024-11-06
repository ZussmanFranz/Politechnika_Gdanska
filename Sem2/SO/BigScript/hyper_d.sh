#!/bin/bash
source functions.sh

while true; do
    ANSWER=`dialog --keep-tite --stdout --title "Main menu" --backtitle "$BACKTITLE"  --menu "menu" 10 140 5 "1" "set cleaning frequency (current: $FREQUENCY)" "2" "set max number of backups (current: $BACKUPS)" "3" "history" "4" "make cleaning"`
    #echo $?
    #echo $WARTOSC

    if [ "$?" = 1 ]; then
        exit
    elif [ -n "$ANSWER" ]; then
        case "$ANSWER" in
            "1")
                # Handle option 1
                TITLE="Cleaning Frequency"

                WARTOSC=`dialog --keep-tite --stdout --title "$TITLE" --backtitle "$BACKTITLE" --inputbox "Current frequency: $FREQUENCY \nEnter new frequency:" 8 60 `
                if [ "$?" = 0 ]; then
                    dialog --keep-tite  --stdout --title "$TITLE" --backtitle "$BACKTITLE" --msgbox "Done\nNew value is $WARTOSC" 8 60 
                    FIELD="FREQUENCY"
                    write_config "$FIELD" "$WARTOSC"
                    FREQUENCY=$(read_config "$FIELD")
                    write_history "FREQUENCY changed: $FREQUENCY"
                fi
                ;;
            "2")
                # Handle option 2
                TITLE="Number of backups"

                WARTOSC=`dialog --keep-tite --stdout --title "$TITLE" --backtitle "$BACKTITLE" --inputbox "Current max number of backups: $BACKUPS \nEnter new number:" 8 60 `
                if [ "$?" = 0 ]; then
                    dialog --keep-tite --stdout --title "$TITLE" --backtitle "$BACKTITLE" --msgbox "Done\nNew value is $WARTOSC" 8 60
                    FIELD="BACKUPS"
                    write_config "$FIELD" "$WARTOSC"
                    BACKUPS=$(read_config "$FIELD")
                    write_history "BACKUPS changed: $BACKUPS"
                fi
                ;;
            "3")
                # Handle option 3
                TITLE="History"

                HISTORY_CONTENT=$(cat "$HISTORY_FILE")
                dialog --keep-tite --stdout --title "$TITLE" --backtitle "$BACKTITLE" --textbox "$HISTORY_FILE" 20 60
                ;;
            "4")
                # Handle option 4
                
                ./cleaner.sh
                ;;
            *)
                echo "Invalid option"
                read
                clear
                exit
                ;;
        esac
    fi
done