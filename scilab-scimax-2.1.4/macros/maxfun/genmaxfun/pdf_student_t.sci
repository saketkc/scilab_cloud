function c=pdf_student_t(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('pdf_student_t',a,b)

endfunction
