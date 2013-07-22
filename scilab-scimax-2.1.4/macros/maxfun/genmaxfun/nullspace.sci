function b=nullspace(a)

if argn(2)~=1 then error(42), end
b=maxevalf('nullspace',a)

endfunction
