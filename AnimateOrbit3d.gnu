set terminal gif animate delay 0.001
set output 'Animated3d.gif'

set xrange[-10 : 10]
set yrange[-10 : 10]
set zrange[-10 : 10]

do for [ii= 1 : 1000] {
    splot 'E3out' every ::1::ii u 3:4:5 w l, \
    'E3out' every ::ii-1::ii u 3:4:5:6:7:8 w vector, \
}
