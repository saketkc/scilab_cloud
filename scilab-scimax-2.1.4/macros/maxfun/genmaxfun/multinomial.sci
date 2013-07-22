function c=multinomial(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('multinomial',a,b)

endfunction
