function c=quantile_geometric(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('quantile_geometric',a,b)

endfunction
