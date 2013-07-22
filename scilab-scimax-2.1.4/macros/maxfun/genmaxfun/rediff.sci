function b=rediff(a)

if argn(2)~=1 then error(42), end
b=maxevalf('rediff',a)

endfunction
