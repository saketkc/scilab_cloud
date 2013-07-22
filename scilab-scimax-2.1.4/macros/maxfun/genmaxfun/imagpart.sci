function b=imagpart(a)

if argn(2)~=1 then error(42), end
b=maxevalf('imagpart',a)

endfunction
