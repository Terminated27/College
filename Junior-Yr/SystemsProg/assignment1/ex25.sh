#!/bin/bash

# Filename: ex21.sh
#
# Problem: Count the number of quotes each person had in the top 100 quote
# list. Then output the list of names in alphabetical order with the number of quotes each.

cat ex21.input | awk '{
        # Find the position of the first dash
        if (match($0,"-")) {
                # Extract the name, using 1-based indexing
                name=substr($0, 1, match($0, "-") - 1);
                
                # Remove leading/trailing spaces from the name
                gsub(/^[ \t]+|[ \t]+$/, "", name);
                
                # Increment the quote count for the person
                quote_count[name]++;
        }
    }
    END {
        # Put all names in an array
        for (name in quote_count) {
            names[count++] = name;
        }

        # Manual sorting of names (Bubble sort)
        for (i = 0; i < count-1; i++) {
            for (j = i+1; j < count; j++) {
                if (names[i] > names[j]) {
                    temp = names[i];
                    names[i] = names[j];
                    names[j] = temp;
                }
            }
        }

        # Print the names and their respective quote counts
        for (i = 0; i < count; i++) {
            print names[i] " had " quote_count[names[i]] " quotes.";
        }
    }'
