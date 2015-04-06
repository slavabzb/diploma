int main()
{
  MatrixRandomFiller filler;
  MatrixMultiplier multiplier;
  MatrixPrinter printer( &std::cout );
  printer.setPrecision( 20 );
  
  std::size_t nRows = 2;
  std::size_t nColumns = 2;
  
  Matrix< double > matrix_a( nRows, nColumns );
  Matrix< double > matrix_b( nRows, nColumns );
  
  filler.fill( matrix_a );
  filler.fill( matrix_b );
  
  printer.print( matrix_a );
  printer.print( matrix_b );
  
  Matrix< double > matrix_c( nRows, nColumns );
  multiplier.multiply( matrix_c, matrix_a, matrix_b );
  
  Matrix< double > matrix_d( nRows, nColumns );
  matrix_d = matrix_a * matrix_b;
  
  printer.print( matrix_c );
  printer.print( matrix_d );
  
  assert( matrix_c == matrix_d );
    
  return 0;
}
