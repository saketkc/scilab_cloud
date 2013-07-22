function c=lsquares_estimates_exact(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('lsquares_estimates_exact',a,b)

endfunction
