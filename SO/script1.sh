#!/bin/bash

# for cdlinux.www.log
grep "\.iso" cdlinux.www.log | cut -d " " -f 1,7-8 | sort -u | cut -d " " -f 2 | grep "\.iso" | sed 's/\.iso.*/.iso/' | grep -o "cdlinux-.*" | sort | uniq -c > temp_cdlinux_www.txt

# for cdlinux.ftp.log
grep "OK DOWNLOAD" cdlinux.ftp.log | grep "\.iso" | cut -d "\"" -f 2,4 | sort -u | sed "s#.*/##" | grep -o "cdlinux-.*" | sort | uniq -c > temp_cdlinux_ftp.txt

# Combine outputs into script.txt
cat temp_cdlinux_www.txt temp_cdlinux_ftp.txt | awk '{sum[$2]+=$1} END {for (i in sum) print sum[i], i}' | sort -nr > script.txt

# Clean up temporary files
rm temp_cdlinux_www.txt temp_cdlinux_ftp.txt

