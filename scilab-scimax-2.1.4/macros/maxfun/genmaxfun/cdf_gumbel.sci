function d=cdf_gumbel(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('cdf_gumbel',a,b,c)

endfunction
