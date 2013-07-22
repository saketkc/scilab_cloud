function b=realpart(a)

if argn(2)~=1 then error(42), end
b=maxevalf('realpart',a)

endfunction
