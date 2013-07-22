function c=legendre_q(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('legendre_q',a,b)

endfunction
