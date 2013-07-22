function d=derivdegree(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('derivdegree',a,b,c)

endfunction
