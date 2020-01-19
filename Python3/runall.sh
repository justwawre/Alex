#!/bin/bash 

chmod +x *.py

for f  in ./*.py
do
  echo $f
  if test -f $f 
  then
      first_line=`sed '1!d' $f`
      if [ "$first_line" == "#!/usr/bin/env python3" ] 
      then
	    clear
            $f
      fi
  fi
done

