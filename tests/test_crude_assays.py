import unittest, json, os

class TestCrudeAssays(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        path = os.path.join(os.path.dirname(__file__), '..', 'data', 'crude_assays.json')
        with open(path, 'r', encoding='utf-8') as f:
            cls.assays = json.load(f)

    def test_cut_mass_balance(self):
        for k, v in self.assays.items():
            if k == 'metadata': continue
            total_cuts = sum(v['yield_cuts_pct'].values())
            self.assertAlmostEqual(total_cuts, 100.0, delta=0.5, msg=f'{k} cut sum != 100%')

    def test_api_gravity_bounds(self):
        for k, v in self.assays.items():
            if k == 'metadata': continue
            self.assertTrue(10.0 <= v['api_gravity'] <= 55.0, f'{k} API out of range')

    def test_sulfur_content_positive(self):
        for k, v in self.assays.items():
            if k == 'metadata': continue
            self.assertTrue(0.0 <= v['sulfur_wt_pct'] <= 6.0, f'{k} sulfur out of range')

    def test_tan_bounds(self):
        for k, v in self.assays.items():
            if k == 'metadata': continue
            self.assertTrue(0.0 <= v['tan_mg_koh_g'] <= 3.0, f'{k} TAN out of range')

    def test_pour_point_bounds(self):
        for k, v in self.assays.items():
            if k == 'metadata': continue
            self.assertTrue(-40.0 <= v['pour_point_c'] <= 50.0, f'{k} pour point invalid')

