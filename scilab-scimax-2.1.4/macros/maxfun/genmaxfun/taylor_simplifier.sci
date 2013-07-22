function b=taylor_simplifier(a)

if argn(2)~=1 then error(42), end
b=maxevalf('taylor_simplifier',a)

endfunction
