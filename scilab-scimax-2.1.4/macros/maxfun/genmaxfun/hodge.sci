function b=hodge(a)

if argn(2)~=1 then error(42), end
b=maxevalf('hodge',a)

endfunction
