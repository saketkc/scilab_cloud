function d=mean_hypergeometric(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('mean_hypergeometric',a,b,c)

endfunction
