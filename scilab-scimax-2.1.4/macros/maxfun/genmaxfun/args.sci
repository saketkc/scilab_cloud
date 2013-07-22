function b=args(a)

if argn(2)~=1 then error(42), end
b=maxevalf('args',a)

endfunction
