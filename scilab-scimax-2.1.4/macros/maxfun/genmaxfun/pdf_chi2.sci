function c=pdf_chi2(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('pdf_chi2',a,b)

endfunction
