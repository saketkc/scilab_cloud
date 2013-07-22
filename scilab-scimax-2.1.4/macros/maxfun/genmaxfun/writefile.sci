function b=writefile(a)

if argn(2)~=1 then error(42), end
b=maxevalf('writefile',a)

endfunction
