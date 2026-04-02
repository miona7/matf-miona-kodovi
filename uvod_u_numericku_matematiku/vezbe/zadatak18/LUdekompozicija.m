function x = LUdekompozicija(A, B)

[L U P] = lu(A);

%  Ax = B  --> PAx = PB
%  LU = PA --> LUx = PB
%  Ux = y  --> Ly = PB
'p'
B = P*B;

[n, m] = size(A);

y = zeros(n, 1);
y(1) = B(1);
for i = 2 : n
    y(i) = B(i) - L(i, :)*y;
end

y

% Ux = y

x = zeros(n, 1);
x(n) = y(n) / U(n, n);

for i = n-1 : -1 : 1
    x(i) = (y(i) - U(i, :)*x) / U(i, i);
end


x