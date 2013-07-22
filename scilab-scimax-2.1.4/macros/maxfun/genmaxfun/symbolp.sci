function b=symbolp(a)

if argn(2)~=1 then error(42), end
b=maxevalf('symbolp',a)

endfunction
