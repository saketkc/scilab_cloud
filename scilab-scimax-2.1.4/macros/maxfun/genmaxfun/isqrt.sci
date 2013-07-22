function b=isqrt(a)

if argn(2)~=1 then error(42), end
b=maxevalf('isqrt',a)

endfunction
