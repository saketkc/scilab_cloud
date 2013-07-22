function b=tracematrix(a)

if argn(2)~=1 then error(42), end
b=maxevalf('tracematrix',a)

endfunction
