function c=cdf_student_t(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('cdf_student_t',a,b)

endfunction
