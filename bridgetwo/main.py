from osrmlib import OSRM
import numpy as np
import pandas as pd


# // Latitude,  Longitude,  Timestamp
# // 45.538450, -73.630014, 1660621345032
# // 45.538223, -73.629229, 1660621347061
# // 45.538102, -73.628773, 1660621349001
# // 45.538008, -73.628473, 1660621350824
# // 45.537922, -73.628210, 1660621352547
# // 45.537873, -73.627926, 1660621354346


osrm = OSRM()


trip = {
    "latitude":  [45.538450,   45.538223,  45.538102,  45.538008,  45.537922,  45.537873],
    "longitude": [-73.630014, -73.629229, -73.628773, -73.628473, -73.628210, -73.627926]
}

res = osrm.match_trip(trip)
print(res)













# from array import array
# import ctypes

# clib = ctypes.cdll.LoadLibrary('build/libbridgetwo.so')

# # clib.test()
# # res = clib.match()



# # clib.pmatch.argtypes = {
# #     # ctypes.c_void_p,
# #     ctypes.c_int,
# #     ctypes.POINTER(ctypes.c_double),
# #     ctypes.POINTER(ctypes.c_double),
# # }

# clib.pmatch.argtypes = {
#     ctypes.c_int
# }


# def convert_doubles_to_pointer(array):
#     n = len(array)
#     array = (ctypes.c_double * n)(*array)
#     return ctypes.cast(array, ctypes.POINTER(ctypes.c_double))


# def convert_ints_to_pointer(array):
#     array = (ctypes.c_int*len(array))(*array)
#     return ctypes.cast(array, ctypes.POINTER(ctypes.c_int))


# longitudes = [1.123423, 3.41413]
# latitudes = [1, 3]

# longitudes = convert_doubles_to_pointer(longitudes),
# latitudes = convert_ints_to_pointer(latitudes)

# print("convert_doubles_c_array: ", longitudes)
# print("convert_ints_c_array: ", latitudes)



# print('clib.match() response: ', res)

# clib.pmatch(
#     ctypes.c_int(2),
#     longitudes,
#     # latitudes
# )