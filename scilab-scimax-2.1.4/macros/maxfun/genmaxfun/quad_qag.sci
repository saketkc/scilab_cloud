function h=quad_qag(a,b,c,d,e,f,g)

if argn(2)~=7 then error(42), end
h=maxevalf('quad_qag',a,b,c,d,e,f,g)

endfunction
