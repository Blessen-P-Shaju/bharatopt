import unittest, math

class TestBlendingRules(unittest.TestCase):
    def test_volume_fraction_sum(self):
        fractions = [0.25, 0.35, 0.40]
        self.assertAlmostEqual(sum(fractions), 1.0, places=6)

