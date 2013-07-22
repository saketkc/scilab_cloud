function d=ode2(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('ode2',a,b,c)

endfunction
