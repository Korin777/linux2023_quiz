set title "Count UTF-8 Excution Time"
set terminal png font " Times_New_Roman,12 "
set xlabel "#utf-8 chracter"
set ylabel "time(ns)"
set output "plot.png"
set key left

plot "output.txt" using 1:2 with linespoints linewidth 2 title "w/o SWAR","output.txt" using 1:3 with linespoints linewidth 2 title "w/ SWAR"
