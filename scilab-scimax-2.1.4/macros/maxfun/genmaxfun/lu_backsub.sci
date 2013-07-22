function c=lu_backsub(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('lu_backsub',a,b)

endfunction
