# author: sparshsah

import unittest
from unittest.mock import patch
# In practice, you'd uncomment the below (replacing `my_module` with your module name).
# from my_module import MyError, my_func_that_raises  # target source code


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
        with self.assertRaises(Exception) as cm:  # context manager
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


class TestMock(unittest.TestCase):
    """
    Demonstrate the `unittest.mock` library.

    Useful for unit-testing code that contains e.g. SQL queries or web requests,
    since mocking `run_my_sql_query()` or `run_my_web_request()`
    is more stable and faster than actually running the underlying queries/requests,
    which depend on external resources. Testing that the queries/requests
    themselves also behave as expected (e.g. actually return what your mock
    object overrides them to return) is a separate self-contained task.

    With that said, a word of caution: A friend of mine once gave me advice that
    I now swear by, which is that having to rely heavily on mocking as part
    of unit-testing your code may be a sign that you can refactor
    to more cleanly separate out transformations from pure data access.
        As a simple and extreme example, the following:
    >>> def my_calc() -> bool:
    ...     return "x" in run_my_sql_query()
    would be better as:
    >>> def _my_calc(data: str) -> bool:
    ...     return "x" in data
    >>> def my_calc() -> bool:
    ...     return _my_calc(data=run_my_sql_query())
        In the first version, you'd need to mock `run_my_sql_query()` to
    effectively unit-test `my_calc()`. But in the second version,
    you can separately unit-test `run_my_sql_query()` and `_my_calc()`,
    and then `my_calc()` becomes a trivial composition of the two
    (which you can choose either to test later as part of
    ["integration testing"](https://martinfowler.com/bliki/IntegrationTest.html)
    or---my preference---just to not test at all).
    """

    def my_method(self):
        return False

    def test_no_mock(self):
        # `None` is falsey
        self.assertFalse(my_func_that_raises())

    # in practice, you'd mock something like `my_module.my_func_that_raises`, not `__main__.my_func_that_raises`
    @patch("__main__.my_func_that_raises", return_value=True)
    def test_mock(self, _):
        self.assertTrue(my_func_that_raises())

    @patch("__main__.my_func_that_raises", return_value=True)
    def test_mock_called(self, mock_func):
        self.assertFalse(mock_func.called)
        self.assertTrue(my_func_that_raises())
        self.assertTrue(mock_func.called)

    @patch("__main__.my_func_that_raises", return_value=True)
    def test_mock_called_with(self, mock_func):
        """Demonstrate the flexibility (therefore also danger!) of mocked functions."""
        # notice: the actual `my_func_that_raises()` wouldn't accept this invalid kwarg!
        self.assertTrue(my_func_that_raises(invalid_kwarg="foobar"))  # pylint: disable=unexpected-keyword-arg
        self.assertTrue(mock_func.called_once_with(invalid_kwarg="foobar"))

    def test_cm_mock(self):
        # in practice, you'd mock something like `my_module`, not `self`
        with patch.object(self, "my_method", return_value=True) as mock_method:  # context manager
            self.assertTrue(self.my_method())
        self.assertTrue(mock_method.called)


if __name__ == "__main__":
    # run this file e.g. from the command line, and watch the magic!
    unittest.main()
