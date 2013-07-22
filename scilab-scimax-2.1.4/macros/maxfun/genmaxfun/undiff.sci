function b=undiff(a)

if argn(2)~=1 then error(42), end
b=maxevalf('undiff',a)

endfunction
