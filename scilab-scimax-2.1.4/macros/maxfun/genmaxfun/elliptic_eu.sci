function c=elliptic_eu(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('elliptic_eu',a,b)

endfunction
