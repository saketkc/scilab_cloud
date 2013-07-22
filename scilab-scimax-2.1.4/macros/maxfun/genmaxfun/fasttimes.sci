function c=fasttimes(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('fasttimes',a,b)

endfunction
