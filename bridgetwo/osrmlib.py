from array import array
import ctypes
from re import L
import numpy as np


def convert_doubles_to_pointer(array):
    n = len(array)
    array = (ctypes.c_double * n)(*array)
    return ctypes.cast(array, ctypes.POINTER(ctypes.c_double))

def convert_ints_to_pointer(array):
    array = (ctypes.c_int*len(array))(*array)
    return ctypes.cast(array, ctypes.POINTER(ctypes.c_int))

class OSRM:
    def __init__(self, libosrmso_path='build/libbridgetwo.so'):
        self.libc = ctypes.cdll.LoadLibrary(libosrmso_path)
        # self.libc.osrm_init.argtypes = (ctypes.c_char_p,)
        self.libc.osrm_init.restype  = ctypes.c_void_p
        self.libc.osrm_match.argtypes = (
            ctypes.c_void_p,
            ctypes.c_int,
            ctypes.POINTER(ctypes.c_double),
            ctypes.POINTER(ctypes.c_double),
            ctypes.POINTER(ctypes.c_double),
            ctypes.POINTER(ctypes.c_double),
        )
        self.osrm = self.libc.osrm_init()
        print('self.osrm -> ', self.osrm)
    
    def __del__(self):
        self.libc.osrm_delete(self.osrm)

    def match_trip(self, trip):
        latitude  = trip['latitude']
        longitude = trip['longitude']
        n = len(longitude)
        matched_long = [0] * n
        matched_lat = [0] * n
        way_id = [0] * n
        matched_long = convert_doubles_to_pointer(matched_long)
        matched_lat  = convert_doubles_to_pointer(matched_lat)
        way_id       = convert_ints_to_pointer(way_id)

        self.libc.osrm_match(
            self.osrm,
            n,
            convert_doubles_to_pointer(longitude),
            convert_doubles_to_pointer(latitude),
            matched_long,
            matched_lat,
        )
        
        ArrayType = ctypes.c_double * n
        array_pointer = ctypes.cast(matched_long, ctypes.POINTER(ArrayType))
        array_pointer = ctypes.cast(matched_lat, ctypes.POINTER(ArrayType))

        matched_long = np.frombuffer(array_pointer.contents)
        matched_lat  = np.frombuffer(array_pointer.contents)

        return matched_long, matched_lat
