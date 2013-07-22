function c=poisint(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('poisint',a,b)

endfunction
