function b=optimize(a)

if argn(2)~=1 then error(42), end
b=maxevalf('optimize',a)

endfunction
