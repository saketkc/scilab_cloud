function f=dblint(a,b,c,d,e)

if argn(2)~=5 then error(42), end
f=maxevalf('dblint',a,b,c,d,e)

endfunction
