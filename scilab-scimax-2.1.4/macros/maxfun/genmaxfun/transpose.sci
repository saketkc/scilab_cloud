function b=transpose(a)

if argn(2)~=1 then error(42), end
b=maxevalf('transpose',a)

endfunction
