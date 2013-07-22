function c=extdiff(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('extdiff',a,b)

endfunction
