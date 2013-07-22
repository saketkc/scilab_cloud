function c=ModeMatrix(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('ModeMatrix',a,b)

endfunction
