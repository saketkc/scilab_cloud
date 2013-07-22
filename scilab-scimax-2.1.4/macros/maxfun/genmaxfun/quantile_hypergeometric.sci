function e=quantile_hypergeometric(a,b,c,d)

if argn(2)~=4 then error(42), end
e=maxevalf('quantile_hypergeometric',a,b,c,d)

endfunction
