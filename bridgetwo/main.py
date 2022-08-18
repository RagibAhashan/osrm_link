from array import array
import ctypes

clib = ctypes.cdll.LoadLibrary('build/libbridgetwo.so')

clib.test()
res = clib.match()



# clib.pmatch.argtypes = {
#     # ctypes.c_void_p,
#     ctypes.c_int,
#     ctypes.POINTER(ctypes.c_double),
#     ctypes.POINTER(ctypes.c_double),
# }

clib.pmatch.argtypes = {
    ctypes.c_int
}


def convert_doubles_to_pointer(array):
    n = len(array)
    array = (ctypes.c_double * n)(*array)
    return ctypes.cast(array, ctypes.POINTER(ctypes.c_double))


def convert_ints_to_pointer(array):
    array = (ctypes.c_int*len(array))(*array)
    return ctypes.cast(array, ctypes.POINTER(ctypes.c_int))


longitudes = [1.123423, 3.41413]
latitudes = [1, 3]

longitudes = convert_doubles_to_pointer(longitudes),
latitudes = convert_ints_to_pointer(latitudes)

print("convert_doubles_c_array: ", longitudes)
print("convert_ints_c_array: ", latitudes)



print('clib.match() response: ', res)

clib.pmatch(
    ctypes.c_int(2),
    longitudes,
    # latitudes
)


class OSRM:
    
    def __init__(self, libosrmso_path='build/libbridgetwo.so'):
        self.libc = ctypes.cdll.LoadLibrary('build/libbridgetwo.so')
    

    # def match(self, longitudes, latitudes):
    #     n = len(longitudes)

        

    #     self.libc.pmatch(

    #     )

























