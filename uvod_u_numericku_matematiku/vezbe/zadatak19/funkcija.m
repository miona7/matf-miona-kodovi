f = @(x) cos(x) - x;

%Test: Njutn(0,0,1e-5)
%Tacna vrednost: fzero(f,0)
%Njutn(0,0,1e-500) bice dostignut maksimalan broj iteracija