set title 'Real Space - MIT' font 'Arial,30'
set view map
set xlabel 'Real' font 'Arial,25'
set ylabel 'Imaginary' font 'Arial,25'
set xtics out
set ytics out
splot 'real.dat' u (($1-500)/50):(($2)/50):3 matrix with image
