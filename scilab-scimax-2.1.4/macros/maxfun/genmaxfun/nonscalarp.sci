function b=nonscalarp(a)

if argn(2)~=1 then error(42), end
b=maxevalf('nonscalarp',a)

endfunction
