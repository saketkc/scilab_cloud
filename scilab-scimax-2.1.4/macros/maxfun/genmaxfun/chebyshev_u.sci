function c=chebyshev_u(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('chebyshev_u',a,b)

endfunction
