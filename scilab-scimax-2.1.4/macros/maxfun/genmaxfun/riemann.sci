function b=riemann(a)

if argn(2)~=1 then error(42), end
b=maxevalf('riemann',a)

endfunction
