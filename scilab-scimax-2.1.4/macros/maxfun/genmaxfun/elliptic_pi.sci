function d=elliptic_pi(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('elliptic_pi',a,b,c)

endfunction
