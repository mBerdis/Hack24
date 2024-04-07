import sys
import ctypes
import struct
import soundfile as sf
from scipy.signal import resample

if len(sys.argv) < 2:
    print("no music file")
    sys.exit(1)

print("hello world1")
filename = sys.argv[1]

s, Fs = sf.read(filename)

downsample_factor = int(Fs / 200)
s_downsampled = resample(s, len(s) // downsample_factor)
Fs_downsampled = Fs // downsample_factor

signal = s_downsampled[:, 0]

Mbox('Your title', 'Your text', 1)
print("hello world2")

minimum = min(signal)
maximum = max(signal)
desiredMax = (89 / maximum)
signal *= desiredMax
new_max = max(signal)
signal = signal.round().astype(int)

for value in signal:
    if 0 < value < 90:
        byte_representation = struct.pack('<B', value)
        binary_string = format(byte_representation[0], '08b')
        print(binary_string, end='')


def Mbox(title, text, style):
    return ctypes.windll.user32.MessageBoxW(0, text, title, style)
