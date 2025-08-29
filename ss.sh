#!/bin/bash

# Get all .xpm files sorted by name
files=(*.xpm)

# Counter starts at 1
count=1

for f in "${files[@]}"; do
    # Format the counter with 2 digits (01, 02, 03...)
    newname=$(printf "%d.xpm" "$count")
    
    echo "Renaming $f -> $newname"
    mv "$f" "$newname"
    
    # Increase counter
    count=$((count + 1))
done
