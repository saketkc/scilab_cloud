function b=trigsimp(a)

if argn(2)~=1 then error(42), end
b=maxevalf('trigsimp',a)

endfunction
