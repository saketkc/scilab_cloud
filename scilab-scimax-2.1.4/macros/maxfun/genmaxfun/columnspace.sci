function b=columnspace(a)

if argn(2)~=1 then error(42), end
b=maxevalf('columnspace',a)

endfunction
