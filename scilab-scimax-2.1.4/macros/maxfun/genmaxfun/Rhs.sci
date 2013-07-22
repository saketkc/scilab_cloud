function b=Rhs(a)

if argn(2)~=1 then error(42), end
b=maxevalf('rhs',a)

endfunction
