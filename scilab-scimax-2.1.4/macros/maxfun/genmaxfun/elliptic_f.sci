function c=elliptic_f(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('elliptic_f',a,b)

endfunction
