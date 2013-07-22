function c=ratdiff(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('ratdiff',a,b)

endfunction
