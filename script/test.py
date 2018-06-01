import multiprocessing
import time

import cmake_example as m

def python_callback():
  print "Hola desde python!"

def python_callback2():
  print "Hola desde python 2!"

if __name__ == "__main__":
  assert m.add(1, 2) == 3
  assert m.subtract(1, 2) == -1
  m.add_step_callback(python_callback)
  m.add_step_callback(lambda: python_callback2())
  m.run()

#def prueba():
#  assert m.add(1, 2) == 3
#  assert m.subtract(1, 2) == -1
#  m.add_step_callback(python_callback)
#  m.add_step_callback(lambda: python_callback2())
#  m.run()
#  import sys
#  sys.exit(1)
#
#if __name__ == "__main__":
#  p = multiprocessing.Process(target=prueba, name="prueba")
#  p.start()
#  time.sleep(5)
#  p.terminate()
#  p.join()

