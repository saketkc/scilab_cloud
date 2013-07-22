function b=poissimp(a)

if argn(2)~=1 then error(42), end
b=maxevalf('poissimp',a)

endfunction
