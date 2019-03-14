#!/bin/bash

konwertuj ()
{
  if [ $1 -gt 8000000 ] || [ $1 -eq 8000000 ] ; then
    wypisz=$(echo "scale=2;$1 / 8000000" | bc -l)
    kon="$wypisz MB"
    echo "$kon"
  elif [ $1 -gt 8000 ] || [ $1 -eq 8000 ] ; then
    wypisz=$(echo "scale=2;$1 / 8000" | bc -l)
    kon="$wypisz KB"
    echo "$kon"
  else
    wypisz=$(echo "scale=2;$1 / 8" | bc -l)
    kon="$wypisz B"
    echo "$kon"
  fi
}
rysuj_wiersz()
{
  i=1
  if ([ 0 -lt $1 ] || [ 0 -eq $1 ]) && ([ $1 -lt 30 ] || [ $1 -eq 30 ]); then
      color=1
  elif ([ 31 -lt $1 ] || [ 31 -eq $1 ]) && ([ $1 -lt 70 ] || [ $1 -eq 70 ]); then
      color=4
  else
    color=2
  fi
  while [ $i -lt $1 ] || [ $i -eq $1 ] ;
  do
    tput cup $((($2))) $(((5)+$i))
    tput setab $color; tput setaf $color;  echo -n "|"
    let i=$i+1
  done
    tput cup $((($2))) $(((1)))
    tput sgr0
    echo "$1%"
    tput cup $((($2))) $(((5)+100))
    tput setaf 2; echo "|"
    tput sgr0
  echo

}

rec=$(cat /proc/net/dev |grep "$1:" |cut -f2 -d':' | awk '{print $1}')
trans=$(cat /proc/net/dev |grep "$1:" |cut -f2 -d':' |awk '{print $9}')
let total_rec="$(echo $rec | awk '{print $1}')+$(echo $rec | awk '{print $2}')+$(echo $rec | awk '{print $3}')"
let total_trans="$(echo $trans | awk '{print $1}')+$(echo $trans | awk '{print $2}')+$(echo $trans | awk '{print $3}')"
awk  '{ printf("System jest uruchomiony %d dni, %d godzin, %d minut, %d sekund\n", ($1/3600/24),($1/3600), ($1/60), $1) }' /proc/uptime
bateria=(`grep "POWER_SUPPLY_CAPACITY=" /sys/class/power_supply/BAT0/uevent`)
echo Stan baterii to ${bateria:22}% #czytaj od 22 znaku do końca
awk  '{ printf("Średnie obciążenie dla ostatniej minuty %f\nŚrednie obciążenie dla ostatnich 5 minut %f\nŚrednie obciążenie dla ostatnich 15 minu %f\nIlość aktywnych procesów / Ilość wszystkich procesów %s\nID najbardziej obciążającego procesu %d\n",$1,$2,$3,$4,$5)}' /proc/loadavg
iteration_amount=1
avg_rec=0;
avg_trans=0;
sleep 1

array=()
while :
do
  tput clear
  awk  '{ printf("System jest uruchomiony %d dni, %d godzin, %d minut, %d sekund\n", ($1/3600/24),($1/3600), ($1/60), $1) }' /proc/uptime
  bateria=(`grep "POWER_SUPPLY_CAPACITY=" /sys/class/power_supply/BAT0/uevent`)
  echo
  echo Stan baterii to ${bateria:22}% #czytaj od 22 znaku do końca
  bat=${bateria:22}

  awk  '{ printf("Średnie obciążenie dla ostatniej minuty %f\nŚrednie obciążenie dla ostatnich 5 minut %f\nŚrednie obciążenie dla ostatnich 15 minu %f\nIlość aktywnych procesów / Ilość wszystkich procesów %s\nID najbardziej obciążającego procesu %d\n",$1,$2,$3,$4,$5)}' /proc/loadavg
  echo
  rec2=$(cat /proc/net/dev |grep "$1:" |cut -f2 -d':' | awk '{print $1}')
  trans2=$(cat /proc/net/dev |grep "$1:" |cut -f2 -d':' |awk '{print $9}')
  let total_rec2="$(echo $rec2 | awk '{print $1}')+$(echo $rec2 | awk '{print $2}')+$(echo $rec2 | awk '{print $3}')"
  let total_trans2="$(echo $trans2 | awk '{print $1}')+$(echo $trans2 | awk '{print $2}')+$(echo $trans2 | awk '{print $3}')"
  let speed_rec=$total_rec2-$total_rec
  let speed_trans=$total_trans2-$total_trans

  result1=`konwertuj $speed_rec`
  result2=`konwertuj $speed_trans`
  echo Aktualna predkosc: Odebrane: $result1, Transmitowane:  $result2

  let avg_rec="($avg_rec*$iteration_amount+$speed_rec) / ($iteration_amount+1)"
  let avg_trans="($avg_trans*$iteration_amount+$speed_trans) / ($iteration_amount+1)"
  let iteration_amount=$iteration_amount+1
  result3=`konwertuj $avg_rec`
  result4=`konwertuj $avg_trans`
  echo Srednia predkosc: Odebrane: $result3, Transmitowane: $result4
  modulo=$(( ($iteration_amount-2) % 20 ))
  if [ $modulo -eq 0 ]; then
      array+=($bat)
  fi
  if [ 4  -lt ${#array[*]} ]; then
      array=(${array[@]:1})
  fi
    echo
    echo
    echo
    echo "                                                  Stan baterii                                              "
    echo
    echo "      --------------------------------------------------------------------------------------------------100%"
      j=17
      for element in ${array[*]}; do
        rysuj_wiersz $element $j
        let j=$j+1
      done




  let total_rec=$total_rec2
  let total_trans=$total_trans2

  sleep 1


done
