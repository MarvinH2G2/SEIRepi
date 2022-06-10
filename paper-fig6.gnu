set terminal 'pdf'
set output 'paper-fig6.pdf'
set xlabel "log(S)" 
set ylabel "log(I)" 
plot 'paper.data' u (log($2)):(log($4)) w l t 'fig6b limit cycle'

