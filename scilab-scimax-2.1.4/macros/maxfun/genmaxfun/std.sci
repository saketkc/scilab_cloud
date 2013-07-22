function b=std(a)

if argn(2)~=1 then error(42), end
b=maxevalf('std',a)

endfunction
