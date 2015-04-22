sizes <- c( 10, 100, 200, 300, 400, 500 )
mul_ext <- c( 0.000165329, 0.156362, 1.23395, 4.28796, 10.2204, 20.557 )
mul_int <- c( 0.000151243, 0.0489345, 0.306424, 1.03737, 2.4036, 4.88812 )

M <- matrix(
  c( mul_int, mul_ext ),
  nrow = 2,
  ncol = length( mul_ext ),
  byrow = TRUE
)

png( filename = "~/Documents/Diploma/Theory/Paper/Figures/MultiplicationTime.png",
  height = 600,
  width = 800,
  bg = "white"
)

barplot( M,
  main = "Умножение матриц",
  xlab = "Размерность матриц, N x N элементов",
  ylab = "Время, с",
  names.arg = sizes,
  beside = TRUE
)

legend_labels <- c( "8 потоков", "1 поток" )

legend(
  "topleft",
  legend_labels,
  bty = "n",
  fill = grey.colors( nrow( M ) )
)

box()

dev.off()
