function b=maybe(a)

if argn(2)~=1 then error(42), end
b=maxevalf('maybe',a)

endfunction
