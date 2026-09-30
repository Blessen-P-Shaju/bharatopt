import unittest, json, os

class TestCrudeAssays(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        path = os.path.join(os.path.dirname(__file__), '..', 'data', 'crude_assays.json')
        with open(path, 'r', encoding='utf-8') as f:
            cls.assays = json.load(f)

