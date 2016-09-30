sizes <- c( 16, 32, 64, 128 )
mul_acc <- c( 1.07313, 3.18533, 4.01695, 4.0335 )

png( filename = "~/Documents/study/diploma/Theory/Paper/Figures/MatSizeResult.png",
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

title( main = "Зависимость ускорения МЭ от размерности задачи" )
title( xlab = "Размерность матриц, N x N элементов" )
title( ylab = "Коэффициент ускорения, t1/t8" )

legend( "bottomright",
  max( mul_acc ),
  "Ускорение",
  pch = 21,
  lty = 1
)

dev.off()
