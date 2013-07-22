function d=contrib_ode(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('contrib_ode',a,b,c)

endfunction
