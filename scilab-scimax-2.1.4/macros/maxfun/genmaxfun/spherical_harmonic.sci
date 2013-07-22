function e=spherical_harmonic(a,b,c,d)

if argn(2)~=4 then error(42), end
e=maxevalf('spherical_harmonic',a,b,c,d)

endfunction
