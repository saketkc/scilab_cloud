function d=std_hypergeometric(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('std_hypergeometric',a,b,c)

endfunction
