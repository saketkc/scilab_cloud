function b=cint(a)

if argn(2)~=1 then error(42), end
b=maxevalf('cint',a)

endfunction
