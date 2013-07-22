function c=stirling(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('stirling',a,b)

endfunction
