function b=macroexpand(a)

if argn(2)~=1 then error(42), end
b=maxevalf('macroexpand',a)

endfunction
