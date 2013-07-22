function c=%sym_get(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('get',a,b)

endfunction
