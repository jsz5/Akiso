#!/bin/bash
i=1
w3m -dump $1 > output1.txt
sleep $2
while [ 0 -lt $i ];
do
  w3m -dump $1 > output2.txt
  page="$1"
  page=$(echo "${page///}")
  now=$(date)

  d=$(diff output1.txt output2.txt)
  if [ "$d" != "" ];  then
      diff -c output1.txt output2.txt > "${page}.${now}.txt"
      git add "${page}.${now}.txt"
      git push
      git commit -m "$i"
      tput clear
      echo "NA STRONIE ZASZŁA ZMIANA"
      
  else
      echo "Strona bez zmian"
  fi

  if [ -e  "${page}.${now}.txt" ]; then
    rm "${page}.${now}.txt"
  fi
  let i=$i+1
  cp -f output2.txt output1.txt
  sleep $2
done
