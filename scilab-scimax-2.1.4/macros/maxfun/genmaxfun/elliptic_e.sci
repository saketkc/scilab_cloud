function c=elliptic_e(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('elliptic_e',a,b)

endfunction
