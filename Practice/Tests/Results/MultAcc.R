sizes <- c( 10, 100, 200, 300, 400, 500 )
mul_acc <- c( 1.09313, 3.19533, 4.02695, 4.1335, 4.25212, 4.20549 )

png( filename = "~/Documents/Diploma/Theory/Paper/Figures/MultiplicationAcceleration.png",
  height = 600,
  width = 800,
  bg = "white"
)

plot( mul_acc,
  type = "o",
  ylim = c( min( mul_acc ) - c( 0.3 ),
            max( mul_acc ) + c( 0.3 )
          ),
  axes = FALSE,
  ann = FALSE
)

grid( col = "darkgray" )

axis( 1,
  at = 1 : length( mul_acc ),
  lab = sizes
)

axis( 2,
  las = 1,
  at = round( seq( from = min( mul_acc ),
    to = max( mul_acc ),
    length.out = 4 ),
  2 )
)

box()

title( main = "Умножение матриц" )
title( xlab = "Размерность матриц, N x N элементов" )
title( ylab = "Коэффициент ускорения" )

legend( "bottomright",
  max( mul_acc ),
  "Ускорение",
  pch = 21,
  lty = 1
)

dev.off()
