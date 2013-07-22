function b=askinteger(a)

if argn(2)~=1 then error(42), end
b=maxevalf('askinteger',a)

endfunction
