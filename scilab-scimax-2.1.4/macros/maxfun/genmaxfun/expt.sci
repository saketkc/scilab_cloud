function c=expt(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('expt',a,b)

endfunction
