function b=rgb2level(a)

if argn(2)~=1 then error(42), end
b=maxevalf('rgb2level',a)

endfunction
