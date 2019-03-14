#!/bin/bash
sciezki=$(ls /proc/[0-9]*/status)
printf "Name\t\tPID\t\tFDsize\t\tState\t\tThreads\n"

for proces in $sciezki; do
        if [ -e $proces ]; then
          cat $proces | while read line
          do
            if [ "$line" != "${line%"Name:"*}" ]; then
              echo $line
            elif [ "$line" != "${line%"State:"*}" ]; then
              echo $line
            elif [ "$line" != "${line%"FDSize:"*}" ]; then
              echo $line
            elif [ "$line" != "${line%"Pid:"*}" ] &&[ "$line" = "${line%"TracerPid:"*}" ] &&[ "$line" = "${line%"PPid:"*}" ]; then
              echo $line
              let amount=$(lsof -p ${line:4} | wc -l)-1
              echo Ilosc otwartych plikow to $amount

            elif [ "$line" != "${line%"Threads:"*}" ]; then
              echo $line
            fi
          done
        fi
      echo
      echo
done
