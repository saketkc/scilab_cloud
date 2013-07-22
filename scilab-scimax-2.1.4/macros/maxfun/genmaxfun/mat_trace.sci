function b=mat_trace(a)

if argn(2)~=1 then error(42), end
b=maxevalf('mat_trace',a)

endfunction
