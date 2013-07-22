function c=hermite(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('hermite',a,b)

endfunction
