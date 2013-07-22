function b=get_lu_factors(a)

if argn(2)~=1 then error(42), end
b=maxevalf('get_lu_factors',a)

endfunction
