# What does this code do ?

- It is a simple iterative solution to the least squares optimization problem called [Landweber Iterations](http://en.wikipedia.org/wiki/Landweber_iteration) 

# PSEUDO - CODE : 

```bash
  α = max(svd(A));
  Init: x0 = 0.
  For i = 1 to MaxIter
      Landweber Solution;
  End
```

- MaxIter is less than 50,000
- Reports the time difference between single thread version and OpemMP implementation
