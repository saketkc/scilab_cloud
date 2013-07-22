function b=op(a)

if argn(2)~=1 then error(42), end
b=maxevalf('op',a)

endfunction
