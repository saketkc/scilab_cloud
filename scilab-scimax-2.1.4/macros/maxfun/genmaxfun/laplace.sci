function d=laplace(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('laplace',a,b,c)

endfunction
