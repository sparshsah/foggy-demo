# target source code
# in practice, you'd uncomment the below (replacing `my_module` with your module name)
# from my_module import MyError, my_func_that_raises
# unit-testing suite
import unittest


# pretend this code defining `MyError` and `my_func_that_raises` actually lives in `my_module`

class MyError(Exception):
    def __init__(self, message: str="MyError!", is_unexpected: bool=False):
        super().__init__(message)
        self.is_unexpected = is_unexpected


def my_func_that_raises(my_err_to_raise: int=-1):
    if my_err_to_raise < 0:
        return
    elif my_err_to_raise == 0:
        raise MyError()
    else:
        raise MyError(is_unexpected=True)


# actual unit tests

class TestSetUpClass(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls.t = 0  # same as putting `t = 0` as a standalone class-level statement

    @classmethod
    def tearDownClass(cls):
        cls.t += 1

    def setUp(self):
        self.__class__.t += 1

    def tearDown(self):
        self.__class__.t += 1

    def test0(self):
        # before this, `setUpClass()` then `setUp()` were run, so this will pass
        self.assertEqual(self.__class__.t, 1)
        # after this, `tearDown()` will be run

    def test1(self):
        # before this, `setUp()` was run again, so this will pass
        self.assertEqual(self.__class__.t, 3)
        # after this, `tearDown()` will be run again
        # finally, `tearDownClass()` will be run


class TestSetUp(unittest.TestCase):
    """Demonstrate that each unit-test func is run from a brand-new, isolated `unittest.TestCase` instance."""

    def __init__(self, *args, **kwargs):
        """https://github.com/python/cpython/blob/1470edd6131c29b8a09ce012cdfee3afa269d553/Lib/unittest/case.py#L323"""
        super().__init__(*args, **kwargs)
        self.t = 0

    def setUp(self):
        self.t += 1

    def tearDown(self):
        self.t += 1

    def test0(self):
        # before this, `setUp()` was run, so this will pass
        self.assertEqual(self.t, 1)
        # after this, `tearDown()` will be run

    def test1(self):
        """
        Now comes the trick: Even though right before this line,
        `setUp()` was run "again", `self.t` will still be `1`!

        Naive programmers like me might expect the following:
        >>> TestSetUp()  # instantiate unittest.TestCase, t == 0
        >>> setUp()  # t == 1
        >>> test0()  # t == 1
        >>> tearDown()  # t == 2
        >>> setUp()  # t == 3
        >>> test1()  # t == 3
        >>> tearDown()  # t == 4

        But in reality, it's:
        >>> TestSetUp()  # instantiate unittest.TestCase, t == 0
        >>> setUp()  # t == 1
        >>> test0()  # t == 1
        >>> tearDown()  # t == 2
        >>> TestSetUp()  # instantiate unittest.TestCase, t == 0 again!!!
        >>> setUp()  # t == 1
        >>> test1()  # t == 1
        >>> tearDown()  # t == 2
        """
        self.assertEqual(self.t, 1)


class TestFloatEqual(unittest.TestCase):

    x: float = 1.0
    y: float = x
    z: float = x + 0.01

    def test_binary_repr_equal(self):
        self.assertEqual(self.__class__.x, self.__class__.y)

    def test_tight_numerical_equal(self):
        self.assertAlmostEqual(self.__class__.x, self.__class__.y)

    def test_loose_numerical_equal(self):
        self.assertAlmostEqual(self.__class__.x, self.__class__.z, delta=0.1)

    def test_not_binary_repr_equal(self):
        self.assertNotEqual(self.__class__.x, self.__class__.z)

    def test_not_numerical_equal(self):
        self.assertNotAlmostEqual(self.__class__.x, self.__class__.z)


class TestRaise(unittest.TestCase):

    def test_no_raise(self):
        try:
            my_func_that_raises()
        except:
            self.assertTrue(False, msg="Should not have raised!")

    def test_raises(self):
        with self.assertRaises(Exception):
            my_func_that_raises(my_err_to_raise=0)

    def test_raises_something_specific_unidiomatically(self):
        with self.assertRaises(Exception) as cm:  # ContextManager
            my_func_that_raises(my_err_to_raise=0)
        self.assertIsInstance(cm.exception, MyError)

    def test_raises_something_specific_idiomatically(self):
        with self.assertRaises(MyError):
            my_func_that_raises(my_err_to_raise=0)

    def test_raises_something_expected(self):
        with self.assertRaises(MyError) as cm:
            my_func_that_raises(my_err_to_raise=0)
        self.assertFalse(cm.exception.is_unexpected)

    def test_raises_something_unexpected(self):
        with self.assertRaises(MyError) as cm:
            my_func_that_raises(my_err_to_raise=1)
        self.assertTrue(cm.exception.is_unexpected)


if __name__ == "__main__":
    # run this file e.g. from the command line, and watch the magic!
    unittest.main()
