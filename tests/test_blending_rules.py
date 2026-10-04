import unittest, math

class TestBlendingRules(unittest.TestCase):
    def test_volume_fraction_sum(self):
        fractions = [0.25, 0.35, 0.40]
        self.assertAlmostEqual(sum(fractions), 1.0, places=6)

    def test_chevron_rvp_index(self):
        rvps = [45.0, 75.0, 60.0]
        vols = [0.3, 0.2, 0.5]
        indices = [r ** 1.25 for r in rvps]
        blend_idx = sum(v * idx for v, idx in zip(vols, indices))
        blend_rvp = blend_idx ** (1.0 / 1.25)
        self.assertTrue(50.0 < blend_rvp < 65.0)

