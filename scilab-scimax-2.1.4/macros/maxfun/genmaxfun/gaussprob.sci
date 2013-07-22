function b=gaussprob(a)

if argn(2)~=1 then error(42), end
b=maxevalf('gaussprob',a)

endfunction
