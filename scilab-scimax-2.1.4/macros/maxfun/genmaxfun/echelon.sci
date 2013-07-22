function b=echelon(a)

if argn(2)~=1 then error(42), end
b=maxevalf('echelon',a)

endfunction
