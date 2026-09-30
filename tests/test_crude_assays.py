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

