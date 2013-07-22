function b=einstein(a)

if argn(2)~=1 then error(42), end
b=maxevalf('einstein',a)

endfunction
