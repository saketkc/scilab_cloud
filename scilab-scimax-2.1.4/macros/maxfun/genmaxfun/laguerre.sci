function c=laguerre(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('laguerre',a,b)

endfunction
