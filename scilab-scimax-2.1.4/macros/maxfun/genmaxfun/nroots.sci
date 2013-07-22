function d=nroots(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('nroots',a,b,c)

endfunction
