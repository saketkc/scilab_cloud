function c=invert_by_lu(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('invert_by_lu',a,b)

endfunction
