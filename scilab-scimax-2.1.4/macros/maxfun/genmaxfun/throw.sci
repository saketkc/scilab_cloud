function b=throw(a)

if argn(2)~=1 then error(42), end
b=maxevalf('throw',a)

endfunction
