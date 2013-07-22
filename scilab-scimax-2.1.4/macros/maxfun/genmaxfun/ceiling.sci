function b=ceiling(a)

if argn(2)~=1 then error(42), end
b=maxevalf('ceiling',a)

endfunction
