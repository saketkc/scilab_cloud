function c=kron_delta(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('kron_delta',a,b)

endfunction
