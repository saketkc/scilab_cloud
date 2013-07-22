function b=unitvector(a)

if argn(2)~=1 then error(42), end
b=maxevalf('unitvector',a)

endfunction
