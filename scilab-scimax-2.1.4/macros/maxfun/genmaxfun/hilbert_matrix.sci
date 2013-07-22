function b=hilbert_matrix(a)

if argn(2)~=1 then error(42), end
b=maxevalf('hilbert_matrix',a)

endfunction
