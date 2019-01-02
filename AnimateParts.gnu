set terminal gif animate delay 0.01
set output 'AnimatedParts.gif'

set xrange[-20 : 10]
set yrange[-10 : 10]

do for [ii= 1 : 100] { 
        plot for [jj = 1:11] 'p'.jj every ::1::ii u 3:4 w l title 'p'.jj, \
        'p'.jj every ::ii-1::ii u 3:4:5:6 w vector title 'p'.jj
}
