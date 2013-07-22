function c=bernpoly(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('bernpoly',a,b)

endfunction
