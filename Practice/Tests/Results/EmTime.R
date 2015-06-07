time_2_threads <- c( 123.642, 71.9629 )
time_8_threads <- c( 77.22, 28.1456 )

M <- matrix(
  c( time_2_threads, time_8_threads ),
  nrow = 2,
  ncol = length( time_8_threads ),
  byrow = TRUE
)

png( filename = "~/Documents/Diploma/Theory/Paper/Figures/EmTime.png",
  height = 600,
  width = 800,
  bg = "white"
)

x_labels <- c( "Используя 2 потока", "Используя 8 потоков" )
barplot( M,
  main = "Время выполнения оптимизации",
  xlab = "",
  ylab = "Время, с",
  names.arg = x_labels,
  beside = TRUE
)

grid( NA, ny = NULL, col = "darkgray" )

legend_labels <- c( "Однопоточный режим", "Многопоточный режим" )

legend(
  "topright",
  legend_labels,
  bty = "n",
  fill = grey.colors( nrow( M ) )
)

box()

dev.off()
