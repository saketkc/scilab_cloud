function f=image(a,b,c,d,e)

if argn(2)~=5 then error(42), end
f=maxevalf('image',a,b,c,d,e)

endfunction
