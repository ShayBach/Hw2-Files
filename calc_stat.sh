#!/bin/bash
# This script gets a course number as argument,check it's validation and
# creates statitcs from the course number grades file -
# histogram, mean, min, max and median

#Check if any argument was given
if (( $#!=1 )); then
    echo "Wrong number of arguments" >&2
    exit 1
fi
course_num=$1
#Check if there is such file in my cwd
file_name=$(ls | grep -i "$course_num".*)
if [[ -f "$course_num" ]] || [[ -f "$file_name" ]]; then
    #Check if there is alrady file named xxxxxx_stat
    if [[ -d "$course_num"_stat ]]; then
        rm -rf "$course_num"_stat
    fi
    mkdir "$course_num"_stat
    #touch "$course_num"_stat/histogram.txt
    if [[ -f "$course_num" ]]; then
        ./hist.exe "$course_num" > "$course_num"_stat/histogram.txt
        #2>/dev/null because we dont want to print the same wrong grades again
        mean=$(./mean.exe "$course_num" 2>/dev/null)
        median=$(./median.exe "$course_num" 2>/dev/null) 
        min=$(./min.exe "$course_num" 2>/dev/null) 
        max=$(./max.exe "$course_num" 2>/dev/null) 
    else
        ./hist.exe "$file_name" > "$course_num"_stat/histogram.txt
        #2>/dev/null because we dont want to print the same wrong grades again
        mean=$(./mean.exe "$file_name" 2>/dev/null)
        median=$(./median.exe "$file_name" 2>/dev/null) 
        min=$(./min.exe "$file_name" 2>/dev/null) 
        max=$(./max.exe "$file_name" 2>/dev/null)
    fi
    statistics="$mean\t$median\t$min\t$max"
    #-e to treat \t as tab and not literly \t
    echo -e "$statistics" > "$course_num"_stat/statistics.txt
    exit 0
else
    echo "Course not found" >&2
    exit 1
fi


