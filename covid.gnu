set terminal 'pdf'
set output 'covid.pdf'
set xrange [1000:1005]
set xlabel "years"
set ylabel "fraction" 
plot 'covid.data' u 1:2 w l t 'S', 'covid.data' u 1:4 w l t 'I', 'covid.data' u 1:5 w l t 'R'
plot  'covid.data' u 1:($6) w l t 'seasonal Rt'

