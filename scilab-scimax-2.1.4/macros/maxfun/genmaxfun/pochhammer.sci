function c=pochhammer(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('pochhammer',a,b)

endfunction
