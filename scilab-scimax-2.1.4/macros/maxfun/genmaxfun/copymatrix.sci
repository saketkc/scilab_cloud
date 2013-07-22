function b=copymatrix(a)

if argn(2)~=1 then error(42), end
b=maxevalf('copymatrix',a)

endfunction
