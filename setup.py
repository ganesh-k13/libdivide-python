from distutils.core import setup, Extension

def main():
    setup(name="read_list",
          version="1.0.0",
          description="Python interface for the read_list function",
          author="Ganesh Kathiresan",
          author_email="ganesh3597@gmail.com",
          ext_modules=[Extension("divpy", ["divpy/floor_divide.c"])])

if __name__ == "__main__":
    main()