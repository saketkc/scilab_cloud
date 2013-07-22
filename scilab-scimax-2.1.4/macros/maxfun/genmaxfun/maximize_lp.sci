function d=maximize_lp(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('maximize_lp',a,b,c)

endfunction
