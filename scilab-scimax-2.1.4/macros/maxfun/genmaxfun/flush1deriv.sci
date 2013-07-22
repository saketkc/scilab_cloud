function c=flush1deriv(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('flush1deriv',a,b)

endfunction
