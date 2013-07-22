function c=partfrac(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('partfrac',a,b)

endfunction
