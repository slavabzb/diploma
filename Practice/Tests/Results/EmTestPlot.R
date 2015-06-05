require( rgl )

x <- seq( from = -10, to = 10, by = 0.5 )
y <- seq( from =  -8, to = 10, by = 0.5 )

f0 <- x[1]^2 + ( y[1] - 2 )^2
plot3d( x[1], y[1], f0, xlab = "X", ylab = "Y", zlab = "Z", col = "red" )

for( i in 2 : length( x ) ) {
  for( j in 2 : length( y ) ) {
    f0 <- x[i]^2 + ( y[j] - 2 )^2
    plot3d( x[i], y[j], f0, col = "red", add = TRUE )
  }
}

#f1 <- x^2 + y^2 - 9
#f2 <- x^2 + ( y - 4 )^2 - 9
spheres3d( x = 0, y = 0, z = 0, radius = 35, alpha = 0.3, col = "blue", add = TRUE )
spheres3d( x = 0, y = 4, z = 0, radius = 35, alpha = 0.3, col = "blue", add = TRUE )
