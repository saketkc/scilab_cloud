function c=pdf_geometric(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('pdf_geometric',a,b)

endfunction
