# target source code
# in practice, you'd uncomment the below (replacing `my_module` with your module name)
# from my_module import MyError, my_func_that_throws
# unit-testing suite
import unittest


# pretend this code defining `MyError` and `my_func_that_throws` actually lives in `my_module`
class MyError(BaseException):
    def __init__(self, message: str="MyError!", is_unexpected: bool=False):
        self.message = message
        self.is_unexpected = is_unexpected


def my_func_that_throws(my_err_to_throw: int=-1):
    if my_err_to_throw < 0:
        return
    elif my_err_to_throw == 0:
        raise MyError()
    else:
        raise MyError(is_unexpected=True)


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


if __name__ == "__main__":
    unittest.main()