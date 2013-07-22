function b=%sym_atan(a)

if argn(2)~=1 then error(42), end
b=maxevalf('atan',a)

endfunction
