function c=charpoly(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('charpoly',a,b)

endfunction
