#!/bin/bash
source functions.sh

# Sort folders by creation time (oldest to newest)
sorted_folders=$(ls -td "$BACKUPS_FOLDER"/*/)

# Count the number of folders
num_folders=$(echo "$sorted_folders" | wc -l)

# If the number of folders exceeds the limit, delete the oldest ones
if [ "$num_folders" -gt "$BACKUPS" ]; then
    # Calculate the number of folders to delete
    num_to_delete=$((num_folders - BACKUPS))

    # Delete the oldest folders
    echo "Deleting $num_to_delete oldest folders..."
    write_history "Deleting $num_to_delete oldest folders..."
    read
    echo "$sorted_folders" | tail -n "$num_to_delete" | xargs sudo rm -rf
fi

# Print the remaining folders (sorted from oldest to newest)
echo "Remaining folders (sorted from oldest to newest):"
echo "$sorted_folders"
write_history "Remaining folders (sorted from oldest to newest): $sorted_folders"
