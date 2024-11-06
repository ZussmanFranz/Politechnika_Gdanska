#!/bin/bash

# Function to read value from config file
read_config() {
    grep "^$1=" "$CONFIG_FILE" | cut -d '=' -f2
}

# Function to write value to config file
write_config() {
    local variable="$1" #variable name, for example "BACKUP"
    local new_value="$2" #new value, for example "5"
    sed -i "s/^$variable=.*/$variable=$new_value/" "$CONFIG_FILE"
}

write_history(){
    echo "$(date '+%d-%m-%Y'): $1" >> history.txt
}

BACKTITLE="Backup cleaner"
CONFIG_FILE="./config.txt"
HISTORY_FILE="./history.txt"

# Read values from config file
FREQUENCY=$(read_config "FREQUENCY")
BACKUPS=$(read_config "BACKUPS")
BACKUPS_FOLDER=$(read_config "PATH")