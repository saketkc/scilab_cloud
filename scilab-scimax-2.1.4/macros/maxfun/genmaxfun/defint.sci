function e=defint(a,b,c,d)

if argn(2)~=4 then error(42), end
e=maxevalf('defint',a,b,c,d)

endfunction
