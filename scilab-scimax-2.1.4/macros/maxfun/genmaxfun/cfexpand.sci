function b=cfexpand(a)

if argn(2)~=1 then error(42), end
b=maxevalf('cfexpand',a)

endfunction
