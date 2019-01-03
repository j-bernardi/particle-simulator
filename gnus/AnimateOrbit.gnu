set terminal gif animate delay 0.001
set output 'AnimatedOrbits.gif'

set xrange[-10 : 10]
set yrange[-10 : 10]

do for [ii= 1 : 1000] {
    plot 'Vout' every ::1::ii u 3:4 w l, \
    'Vout' every ::ii-1::ii u 3:4:5:6 w vector, \
    'Eout' every ::1::ii u 3:4 w l, \
    'Eout' every ::ii-1::ii u 3:4:5:6 w vector, \
}
