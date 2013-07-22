function d=cdf_normal(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('cdf_normal',a,b,c)

endfunction
