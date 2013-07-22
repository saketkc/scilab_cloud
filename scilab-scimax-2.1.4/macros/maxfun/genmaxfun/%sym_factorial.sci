function b=%sym_factorial(a)

if argn(2)~=1 then error(42), end
b=maxevalf('factorial',a)

endfunction
