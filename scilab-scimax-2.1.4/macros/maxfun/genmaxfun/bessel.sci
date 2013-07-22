function c=bessel(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('bessel',a,b)

endfunction
