function d=powerseries(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('powerseries',a,b,c)

endfunction
