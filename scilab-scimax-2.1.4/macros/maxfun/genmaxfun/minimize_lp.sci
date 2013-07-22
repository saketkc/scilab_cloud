function d=minimize_lp(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('minimize_lp',a,b,c)

endfunction
