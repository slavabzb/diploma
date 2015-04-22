threads <- c( 1, 2, 4, 6, 8 )
time <- c( 19.1375, 10.6722, 6.82628, 5.59582, 4.8632 )

png( filename = "~/Documents/Diploma/Theory/Paper/Figures/ThreadsNumberTime.png",
  height = 600,
  width = 800,
  bg = "white"
)

plot( time,
  type = "o",
  ylim = c( min( time ) - c( 0.3 ),
            max( time ) + c( 0.3 )
          ),
  axes = FALSE,
  ann = FALSE
)

axis( 1,
  at = 1 : length( time ),
  lab = threads
)

axis( 2,
  las = 1,
  at = round( seq( from = min( time ),
    to = max( time ),
    length.out = 4 ),
  2 )
)

box()

title( main = "Зависимость времени умножение матриц\nот количества используемых потоков" )
title( xlab = "Количество потоков" )
title( ylab = "Время, с" )

legend( "topright",
  max( time ),
  "Время",
  pch = 21,
  lty = 1
)

dev.off()
