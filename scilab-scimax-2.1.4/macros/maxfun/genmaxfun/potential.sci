function b=potential(a)

if argn(2)~=1 then error(42), end
b=maxevalf('potential',a)

endfunction
