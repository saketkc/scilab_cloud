function c=polydecomp(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('polydecomp',a,b)

endfunction
