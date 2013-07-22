function b=conjugate(a)

if argn(2)~=1 then error(42), end
b=maxevalf('conjugate',a)

endfunction
