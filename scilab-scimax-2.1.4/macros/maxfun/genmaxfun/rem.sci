function c=rem(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('rem',a,b)

endfunction
