function b=rationalize(a)

if argn(2)~=1 then error(42), end
b=maxevalf('rationalize',a)

endfunction
