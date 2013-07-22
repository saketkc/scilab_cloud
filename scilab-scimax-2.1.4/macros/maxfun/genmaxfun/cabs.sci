function b=cabs(a)

if argn(2)~=1 then error(42), end
b=maxevalf('cabs',a)

endfunction
