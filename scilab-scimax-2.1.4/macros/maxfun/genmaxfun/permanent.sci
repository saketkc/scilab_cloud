function c=permanent(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('permanent',a,b)

endfunction
