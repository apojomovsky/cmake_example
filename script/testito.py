#!/usr/bin/env python2.7
#
# Copyright 2017 Toyota Research Institute
#

"""Unit tests for the simulation_runner python binding"""

import time
import unittest
import prueba_bindings


class TestSimulationRunnerPy(unittest.TestCase):
    """
    Unit tests for the simulation_runner python binding
    """
    SIMULATION_STEP = 0.001

    def __init__(self, *args, **kwargs):
        super(TestSimulationRunnerPy, self).__init__(*args, **kwargs)
        self.callback_called = False
        self.prueba = None

    def setUp(self):
        self.callback_called = False
        self.prueba = prueba_bindings.Prueba()
        self.prueba.add_step_callback(self.callback_test)

    def callback_test(self):
        """Sets a flag to True."""
        self.callback_called = True
        print("Python callback!")

    def test_callback_when_paused(self):
        """Creates a simulator runner and runs a simulation step,
        verifying that the registered python callback was called.
        """
        # Checks that callback hasn't been called.
        self.assertFalse(self.callback_called)

        self.prueba.start()

        for i in range(10):
            print ("Python")
            time.sleep(0.2)

        # Checks that callback has been called.
        self.assertTrue(self.callback_called)

if __name__ == '__main__':
    unittest.main()

