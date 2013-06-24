mode(2)
//Example 8.1



//Given 
Kp=0.10;//equillibrium constant at 300K
Pa=20;// Partial pressure of A in atm
Pm=1.0;///partial pressure of M in atm
T=300;//Temperature in K
R=8.314;// gas constant in J K^-1 mol^-1
//To determine the free energy
Qp=Pm/Pa;
delG=R*T*log(Qp/Kp);//free energy change
mprintf('(a) delG = %f J mol^-1',delG);
delG0=-R*T*log(Kp);//standard free energy
mprintf('\n (b) standard free energy = %f J mol^-1',delG0);
mprintf('\n (c) Since delG is negetive,the reaction proceeds spontaneously in forward direction')
//end

 quit();