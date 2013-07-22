function c=contract(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('contract',a,b)

endfunction
