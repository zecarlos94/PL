#! /usr/local/bin/gawk -f
# Exercicio 1

BEGIN { FS="{";
        LT = "<html><head><meta charset='utf8'></head><body>";
        head=0;
      }

/^@.*/{gsub("@","");array[$1]++;}

END {for(i in array) { if(head==0) print LT "<h1> BibTex File </h1>" > "count.html";
                       head=1;
                       print "<li> <a>" i " => " array[i] "</a> </li>"  >  "count.html";
                      }
    }
