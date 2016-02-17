#! /bin/tcsh

echo This script assumes that your timetest program is named timetest3.out.
echo The times of the three runs for each ADT are placed in the file \"results\"
echo "File ADT# Time#1       Ignore" > results


set fileNum = 1
while ($fileNum < 5)    # files 1-4
  set ADT = 1
  echo Running File{$fileNum}.dat for all ADTs
  echo "File ADT# Time#1       Ignore"
  while ($ADT < 10)  # 1 - 9 but not 7 
    echo File{$fileNum}.dat > tt.tmp
    echo $ADT >> tt.tmp
    echo 0 >> tt.tmp
    echo -n File{$fileNum}  $ADT "  " | tee -a "results"
    timeout 300s ./timetest3.out < tt.tmp | awk '/CPU/ {printf("%s     ", $6)}' | tee -a "results"
    echo " " | tee -a "results"
    @ ADT ++
  end # while adt 1-9

  if ($ADT == 10)  then # 10
    echo File{$fileNum}.dat > tt.tmp
    echo $ADT >> tt.tmp
    echo 3 >> tt.tmp        # M = 3
    echo 1 >> tt.tmp        # L = 1
    echo 0 >> tt.tmp
    echo -n File{$fileNum}  $ADT "  " | tee -a "results"
    ./timetest3.out < tt.tmp | awk '/CPU/ {printf("%s     ", $20)}' | tee -a "results"
    echo " " | tee -a "results"
    @ ADT ++
  endif # if adt 10

  if ($ADT == 11)  then # seperate chaining
    echo File{$fileNum}.dat > tt.tmp
    echo $ADT >> tt.tmp
    echo 500000 >> tt.tmp        # load factor 1
    echo 0 >> tt.tmp
    echo -n File{$fileNum}  $ADT "  " | tee -a "results"
    ./timetest3.out < tt.tmp | awk '/CPU/ {printf("%s     ", $15)}' | tee -a "results"
    echo " " | tee -a "results"
    @ ADT ++
  endif # if adt 11

  if ($ADT == 12 || $ADT == 14)  then # quad probing
    echo File{$fileNum}.dat > tt.tmp
    echo $ADT >> tt.tmp
    echo 1000000 >> tt.tmp        # load factor .5
    echo 0 >> tt.tmp
    echo -n File{$fileNum}  $ADT "  " | tee -a "results"
    ./timetest3.out < tt.tmp | awk '/CPU/ {printf("%s     ", $15)}' | tee -a "results"
    echo " " | tee -a "results"
    @ ADT ++
  endif # if adt 12

  if ($ADT == 13)  then # binheap
    echo File{$fileNum}.dat > tt.tmp
    echo $ADT >> tt.tmp
    echo 0 >> tt.tmp
    echo -n File{$fileNum}  $ADT "  " | tee -a "results"
    ./timetest3.out < tt.tmp | awk '/CPU/ {printf("%s     ", $6)}' | tee -a "results"
    echo " " | tee -a "results"
    @ ADT ++
  endif # if adt 13

  if ($ADT == 12 || $ADT == 14)  then # quad probing ptr
    echo File{$fileNum}.dat > tt.tmp
    echo $ADT >> tt.tmp
    echo 1000000 >> tt.tmp        # load factor .5
    echo 0 >> tt.tmp
    echo -n File{$fileNum}  $ADT "  " | tee -a "results"
    ./timetest3.out < tt.tmp | awk '/CPU/ {printf("%s     ", $15)}' | tee -a "results"
    echo " " | tee -a "results"
    @ ADT ++
  endif # if adt 14


  @ fileNum ++
end # while more files
