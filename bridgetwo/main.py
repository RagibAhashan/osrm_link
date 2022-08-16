import ctypes

clib = ctypes.cdll.LoadLibrary('build/libbridgetwo.so')

clib.test()
res = clib.match()

print('clib.match() response: ', res)