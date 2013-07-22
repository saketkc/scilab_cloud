function b=%th(a)

if argn(2)~=1 then error(42), end
b=maxevalf('%th',a)

endfunction
