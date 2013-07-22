function b=last(a)

if argn(2)~=1 then error(42), end
b=maxevalf('last',a)

endfunction
