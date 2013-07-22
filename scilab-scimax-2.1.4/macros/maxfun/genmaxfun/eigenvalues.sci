function b=eigenvalues(a)

if argn(2)~=1 then error(42), end
b=maxevalf('eigenvalues',a)

endfunction
