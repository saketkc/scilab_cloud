function d=mnewton(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('mnewton',a,b,c)

endfunction
