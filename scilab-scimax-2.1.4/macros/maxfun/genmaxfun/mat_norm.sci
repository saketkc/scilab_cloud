function b=mat_norm(a)

if argn(2)~=1 then error(42), end
b=maxevalf('mat_norm',a)

endfunction
