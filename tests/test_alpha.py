import cv_extensions as m
from PIL import Image
import numpy as np

def test_alpha():
    im1 = Image.new('RGBA', (100, 100), (255, 0, 0, 50))
    im2 = Image.new('RGBA', (100, 100), (0, 255, 0, 50))

    im3 = np.array(im1.copy())
    im4 = np.array(im2.copy())

    im1.alpha_composite(im2)
    im3 = m.alpha_composite(im3, im4)

    assert np.all(np.array(im1) == im3), "alpha_composite failed"

if __name__ == "__main__":
    test_alpha()
