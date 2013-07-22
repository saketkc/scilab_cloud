function j=parametric_surface(a,b,c,d,e,f,g,h,i)

if argn(2)~=9 then error(42), end
j=maxevalf('parametric_surface',a,b,c,d,e,f,g,h,i)

endfunction
