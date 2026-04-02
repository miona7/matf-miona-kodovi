Y = 1:5;          
n = length(Y);
tol = 10^(-5);    
x0 = zeros(1,n);  

X = zeros(1, n);

for i = 1 : n
    X(i) = Njutn(x0(i), Y(i), tol);
end

disp(['X: ' num2str(X, 5)]);
disp(['Y: ' num2str(Y, 5)]);
