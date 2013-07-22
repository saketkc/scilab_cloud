function c=ode_check(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('ode_check',a,b)

endfunction
