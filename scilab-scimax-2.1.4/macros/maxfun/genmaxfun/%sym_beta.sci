function c=%sym_beta(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('beta',a,b)

endfunction
