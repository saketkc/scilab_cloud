function b=batch(a)

if argn(2)~=1 then error(42), end
b=maxevalf('batch',a)

endfunction
