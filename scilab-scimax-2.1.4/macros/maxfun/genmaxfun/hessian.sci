function c=hessian(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('hessian',a,b)

endfunction
