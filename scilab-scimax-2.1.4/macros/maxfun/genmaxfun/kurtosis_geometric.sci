function b=kurtosis_geometric(a)

if argn(2)~=1 then error(42), end
b=maxevalf('kurtosis_geometric',a)

endfunction
