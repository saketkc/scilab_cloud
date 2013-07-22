function d=pdf_normal(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('pdf_normal',a,b,c)

endfunction
