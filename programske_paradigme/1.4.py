n = int(input("Unesite ceo broj: "))

if n % 5 == 0:
    print("Uneti broj je deljiv da 5") 
elif n % 5 == 1:
    print("Uneti broj daje ostatak 1 pri deljenju sa 5") 
elif n % 5 == 2:
    print("Uneti broj daje ostatak 2 pri deljenju sa 5") 
elif n % 5 == 3:
    print("Uneti broj daje ostatak 3 pri deljenju sa 5") 
elif n % 5 == 4:
    print("Uneti broj daje ostatak 4 pri deljenju sa 5")
else:
    print("Greska")

print("for")
for i in range(n):
    print(i)

print("while")
i = 0
while i < n:
    print(i)
    i += 1