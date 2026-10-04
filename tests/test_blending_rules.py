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

    def test_flash_point_blending_index(self):
        fps = [40.0, 65.0]
        vols = [0.4, 0.6]
        indices = [10 ** (-0.06 * fp) for fp in fps]
        blend_idx = sum(v * idx for v, idx in zip(vols, indices))
        blend_fp = -math.log10(blend_idx) / 0.06
        self.assertTrue(38.0 <= blend_fp <= 55.0)

    def test_diesel_sulfur_compliance(self):
        sulfurs = [8.0, 9.5, 7.0]
        vols = [0.5, 0.3, 0.2]
        blend_s = sum(v * s for v, s in zip(vols, sulfurs))
        self.assertLessEqual(blend_s, 10.0)

