function Q=sym2poly(P,x)

Q=poly2coef(P,x)
Q=poly(eval(~Q),x,'coeff')

endfunction
