function b=mat_cond(a)

if argn(2)~=1 then error(42), end
b=maxevalf('mat_cond',a)

endfunction
