function d=genfact(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('genfact',a,b,c)

endfunction
