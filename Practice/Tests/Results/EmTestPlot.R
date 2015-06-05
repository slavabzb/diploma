M <- mesh( seq( -100, 100, length.out = 80 ),
           seq( -100, 100, length.out = 80 ) )
x <- M$x
y <- M$y

f0 <- x^2 + ( y - 2 )^2
f1 <- x^2 + y^2 - 9
f2 <- x^2 + ( y - 4 )^2 - 9

df <- data.frame(
  x = c( 0 ),
  y = c( 0 ),
  z = c( 0 )
)

library(rgl)
spheres3d(x = 1, y = 1, z = 1, radius = 1)

#library(plot3D)
#surf3D( x, y, f1, colkey = FALSE )
#surf3D( x, y, f1, colkey = FALSE, add = TRUE )
#surf3D( x, y, f2, colkey = FALSE, add = TRUE )
