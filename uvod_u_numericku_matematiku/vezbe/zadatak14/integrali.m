function integrali(f)

I1 = integral(f, -1, 1);
disp(I1)

I2 = integral(@(x) f(x).*sin(x), -1, 1);
disp(I2)

L = legendre_poly(5);

I3 = integral(@(x) f(x).*polyval(L{6}, x), -1, 1);
disp(I3)

I4 = integral(@(x) polyval(L{4}, x).*polyval(L{6}, x), -1, 1);
disp(I4)