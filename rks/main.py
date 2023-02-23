import os

from utils.error import Error

filename = os.path.abspath("../tests/test.rks")
file = open(filename, 'r')
bin_file = open(filename[:-4], 'w')