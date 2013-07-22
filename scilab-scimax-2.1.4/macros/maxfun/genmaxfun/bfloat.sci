function b=bfloat(a)

if argn(2)~=1 then error(42), end
b=maxevalf('bfloat',a)

endfunction
