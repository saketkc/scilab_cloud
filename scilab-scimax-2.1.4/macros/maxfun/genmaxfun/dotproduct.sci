function c=dotproduct(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('dotproduct',a,b)

endfunction
