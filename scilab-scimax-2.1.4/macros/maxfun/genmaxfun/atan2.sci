function c=atan2(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('atan2',a,b)

endfunction
