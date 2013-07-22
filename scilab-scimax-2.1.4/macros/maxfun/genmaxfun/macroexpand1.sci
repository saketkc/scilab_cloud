function b=macroexpand1(a)

if argn(2)~=1 then error(42), end
b=maxevalf('macroexpand1',a)

endfunction
