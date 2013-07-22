function b=trunc(a)

if argn(2)~=1 then error(42), end
b=maxevalf('trunc',a)

endfunction
