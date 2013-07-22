function b=taylorinfo(a)

if argn(2)~=1 then error(42), end
b=maxevalf('taylorinfo',a)

endfunction
