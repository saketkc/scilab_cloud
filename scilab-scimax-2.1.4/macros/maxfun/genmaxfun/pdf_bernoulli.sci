function c=pdf_bernoulli(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('pdf_bernoulli',a,b)

endfunction
