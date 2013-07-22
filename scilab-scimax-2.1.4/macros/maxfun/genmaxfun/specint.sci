function d=specint(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('specint',a,b,c)

endfunction
