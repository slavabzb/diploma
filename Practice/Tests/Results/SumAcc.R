sizes <- c( 10, 100, 200, 300, 400, 500 )
add_acc <- c( 1.11829, 1.21471, 1.35368, 1.36964, 1.31579, 1.36044 )

png( filename = "~/Documents/Diploma/Theory/Paper/Figures/SummarizingAcceleration.png",
  height = 600,
  width = 800,
  bg = "white"
)

plot( add_acc,
  type = "o",
  ylim = c( min( add_acc ) - c( 0.3 ),
            max( add_acc ) + c( 0.3 )
          ),
  axes = FALSE,
  ann = FALSE
)

grid( col = "darkgray" )

axis( 1,
  at = 1 : length( add_acc ),
  lab = sizes
)

axis( 2,
  las = 1,
  at = round( seq( from = min( add_acc ),
    to = max( add_acc ),
    length.out = 4 ),
  2 )
)

box()

title( main = "Сложение матриц" )
title( xlab = "Размерность матриц, N x N элементов" )
title( ylab = "Коэффициент ускорения" )

legend( "bottomright",
  max( add_acc ),
  "Ускорение",
  pch = 21,
  lty = 1
)

dev.off()
