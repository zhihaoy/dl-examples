from ctypes import CDLL, c_double


x = (c_double * 3)(1., 2., 3.)
y = (c_double * 3)(4., -5., 6.)
repromath = CDLL(r'$<TARGET_FILE:repromath>')
ddot = repromath[r'$<IF:$<PLATFORM_ID:Windows>,?ddot@repromath@@YANHPEBN0@Z,_ZN9repromath4ddotEiPKdS1_>']
ddot.restype = c_double

print("result = {}".format(ddot(3, x, y)));

