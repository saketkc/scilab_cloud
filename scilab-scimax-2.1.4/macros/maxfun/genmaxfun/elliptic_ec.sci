function b=elliptic_ec(a)

if argn(2)~=1 then error(42), end
b=maxevalf('elliptic_ec',a)

endfunction
