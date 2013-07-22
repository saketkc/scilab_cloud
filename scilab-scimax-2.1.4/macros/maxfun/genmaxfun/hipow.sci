function c=hipow(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('hipow',a,b)

endfunction
