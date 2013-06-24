driver("PNG");

 xinit("/home/cfduser/SANDBOX/scilab_cloud/graphs/3/2013-06-2106:00:27.png");
mode(2)
// Calculate the magnitude of Force and limiting error

E=200*10^9;
L=25*10^-3;
b=4.75*10^-3;
d=0.9*10^-3;
I=(b*d^3)/12;
x=2.5*10^-3;
F=(3*E*I*x)/(L^3);
disp(F,'Magnitude of Force (N)=')
dE_pu=0/E; // per unit error in E
db_pu=0.0075/b; 
dd_pu=0.0075/d;  
dx_pu=0.025/x; 
dL_pu=0.025/L;
dF_pu= (dE_pu+db_pu+3*dd_pu+dx_pu+3*dL_pu)*10^-3;

disp(dF_pu,'limiting error in force (N)=+/-') 

xend();

quit();