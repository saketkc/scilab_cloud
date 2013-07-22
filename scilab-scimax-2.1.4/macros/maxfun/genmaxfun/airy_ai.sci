function b=airy_ai(a)

if argn(2)~=1 then error(42), end
b=maxevalf('airy_ai',a)

endfunction
