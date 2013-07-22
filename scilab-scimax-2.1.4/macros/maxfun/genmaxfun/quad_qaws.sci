function j=quad_qaws(a,b,c,d,e,f,g,h,i)

if argn(2)~=9 then error(42), end
j=maxevalf('quad_qaws',a,b,c,d,e,f,g,h,i)

endfunction
