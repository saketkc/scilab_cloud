function d=pade(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('pade',a,b,c)

endfunction
