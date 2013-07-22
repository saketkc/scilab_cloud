function b=elliptic_kc(a)

if argn(2)~=1 then error(42), end
b=maxevalf('elliptic_kc',a)

endfunction
