import matplotlib.pyplot as plt

numbers = []
for i in range(100000, 2000001, 100000):
    numbers.append(i)

with open("collisions.txt", "r") as f:
    RS_str   = f.readline()
    JS_str   = f.readline()
    ELF_str  = f.readline()
    PJW_str  = f.readline()
    BKDR_str = f.readline()
    SDBM_str = f.readline()
    DJB_str  = f.readline()
    DEK_str  = f.readline()
    AP_str   = f.readline()

RS   = list(map(int,   RS_str.split()))
JS   = list(map(int,   JS_str.split()))
ELF  = list(map(int,  ELF_str.split()))
PJW  = list(map(int,  PJW_str.split()))
BKDR = list(map(int, BKDR_str.split()))
SDBM = list(map(int, SDBM_str.split()))
DJB  = list(map(int,  DJB_str.split()))
DEK  = list(map(int,  DEK_str.split()))
AP   = list(map(int,   AP_str.split()))

plt.plot(numbers, RS,   label='RSHash',   color = 'blue')
plt.plot(numbers, JS,   label='JSHash',   color = 'green')
plt.plot(numbers, BKDR, label='BKDRHash', color = 'brown')
plt.plot(numbers, SDBM, label='SDBMHash', color = 'purple')
plt.plot(numbers, DJB,  label='DJBHash',  color = 'lime')
plt.plot(numbers, DEK,  label='DEKHash',  color = 'deeppink')
plt.plot(numbers, AP,   label='JSHash',   color = 'aqua')

plt.xlabel("Number of strings", fontsize = 10)
plt.ylabel("Number of collisions", fontsize = 10)
plt.legend()
plt.savefig('RS_JS_BKDR_SDBM_DJB_DEK_AP.png')
plt.show()

plt.plot(numbers, ELF,  label='ELFHash',  color = 'red')
plt.plot(numbers, PJW,  label='PJWHash',  color = 'yellow')

plt.xlabel("Number of strings", fontsize = 10)
plt.ylabel("Number of collisions", fontsize = 10)
plt.legend()

plt.savefig('ELF_PJW.png')