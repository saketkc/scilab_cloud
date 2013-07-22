function c=chebyshev_t(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('chebyshev_t',a,b)

endfunction
