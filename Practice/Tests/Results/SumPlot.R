sizes <- c( 10, 100, 200, 300, 400, 500 )
add_ext <- c( 1.65453e-05, 0.00214674, 0.00678715, 0.0158534, 0.0276726, 0.0430147 )
add_int <- c( 1.47952e-05, 0.00176729, 0.00501385, 0.0115748, 0.0210312, 0.0316182 )

M <- matrix(
  c( add_int, add_ext ),
  nrow = 2,
  ncol = length( add_ext ),
  byrow = TRUE
)

png( filename = "~/Documents/Diploma/Theory/Paper/Figures/SummarizingTime.png",
  height = 600,
  width = 800,
  bg = "white"
)

barplot( M,
  main = "Сложение матриц",
  xlab = "Размерность матриц, N x N элементов",
  ylab = "Время, с",
  names.arg = sizes,
  beside = TRUE
)

grid( NA, ny = NULL, col = "darkgray" )

legend_labels <- c( "8 потоков", "1 поток" )

legend(
  "topleft",
  legend_labels,
  bty = "n",
  fill = grey.colors( nrow( M ) )
)

box()

dev.off()
