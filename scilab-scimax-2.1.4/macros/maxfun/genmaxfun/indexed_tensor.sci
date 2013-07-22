function b=indexed_tensor(a)

if argn(2)~=1 then error(42), end
b=maxevalf('indexed_tensor',a)

endfunction
