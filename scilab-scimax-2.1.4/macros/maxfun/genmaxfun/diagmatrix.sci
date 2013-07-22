function c=diagmatrix(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('diagmatrix',a,b)

endfunction
