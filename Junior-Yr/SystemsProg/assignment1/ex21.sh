#!/bin/bash

# Filename: ex21.sh
#
# Problem: Count the number of quotes each person had in the top 100 quote
# list. Then output the list of names in alphabetical order with the number of quotes each.

cat ex21.input | awk '{
        if (match($0,"-")) {
                name=substr($0, 1, match($0, "-") - 1);
                gsub(/^[ \t]|[ \t]$/, "", name);
                quote_count[name]++;
        }
    }
    END {
        for (name in quote_count) {
            names[count++] = name;
        }

        #sort names


        for (i = 0; i < count; i++) {
            print names[i] " had " quote_count[names[i]] " quotes.";
        }
    }' > ex21.output

sort -o ex21.output ex21.output
cat ex21.output
