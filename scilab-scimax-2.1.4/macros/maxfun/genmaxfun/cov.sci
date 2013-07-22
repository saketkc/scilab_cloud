function b=cov(a)

if argn(2)~=1 then error(42), end
b=maxevalf('cov',a)

endfunction
