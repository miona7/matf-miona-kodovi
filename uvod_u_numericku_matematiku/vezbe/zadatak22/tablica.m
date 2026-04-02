%X=0:0.1:0.5;
%F=exp(X)-2*(X-1).^2;
%Test: [I,Y,x]=nula(0,0.5,1e-5,15) %zadovoljena tacnost tol
%Test: [I,Y,x]=nula(0,0.5,1e-5,4)  %zadovoljen max br iteracija iterM
%Test: [I,Y,x]=nula(0,0.5,1e-5,6)  %zadovoljena je tacnost i dostignut max
                                   %br iteravija iterM

% drugi primer
X=0.5:0.1:1;
F=exp(-X)-X.^3+0.2;
%Test: [I,Y,x]=nula(0.5,1,1e-4,10) %zadovoljena tacnost tol
%Test: [I,Y,x]=nula(0.5,1,1e-4,3)  %zadovoljen max br iteracija iterM
%Test: [I,Y,x]=nula(0.5,1,1e-4,5)  %zadovoljena je tacnost i dostignut max
                                   %br iteravija iterM
