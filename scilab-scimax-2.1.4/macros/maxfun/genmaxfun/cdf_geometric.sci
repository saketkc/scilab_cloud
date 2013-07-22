function c=cdf_geometric(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('cdf_geometric',a,b)

endfunction
