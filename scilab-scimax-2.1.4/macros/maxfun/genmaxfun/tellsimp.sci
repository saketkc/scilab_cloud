function c=tellsimp(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('tellsimp',a,b)

endfunction
