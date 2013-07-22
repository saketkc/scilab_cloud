function b=airy_dai(a)

if argn(2)~=1 then error(42), end
b=maxevalf('airy_dai',a)

endfunction
