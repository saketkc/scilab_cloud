function h=implicit(a,b,c,d,e,f,g)

if argn(2)~=7 then error(42), end
h=maxevalf('implicit',a,b,c,d,e,f,g)

endfunction
