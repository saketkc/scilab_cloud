function b=unit_step(a)

if argn(2)~=1 then error(42), end
b=maxevalf('unit_step',a)

endfunction
