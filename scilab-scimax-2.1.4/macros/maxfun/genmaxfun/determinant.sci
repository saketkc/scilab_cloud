function b=determinant(a)

if argn(2)~=1 then error(42), end
b=maxevalf('determinant',a)

endfunction
