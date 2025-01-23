from setuptools import setup
from setuptools.command.install import install
import shutil
import os

# Path to the compiled .so file
SO_FILE = "build_debug/python_binding/pybind_test.cpython-38-x86_64-linux-gnu.so"

# Custom install command to move the .so file to the appropriate directory
class CustomInstall(install):
    def run(self):
        install.run(self)
        # Destination site-packages directory
        site_packages_dir = self.install_lib
        
        # Ensure the .so file exists
        if not os.path.exists(SO_FILE):
            raise FileNotFoundError(f"Compiled .so file not found: {SO_FILE}")
        
        shutil.copy(SO_FILE, site_packages_dir)
        print(f"Copied {SO_FILE} to {site_packages_dir}")

setup(
    name="pybind_test",  # Package name
    version="0.1.0",
    description="A Python-C++ binding pybind_test",
    py_modules=["pybind_test"],  # Module name without extension
    cmdclass={"install": CustomInstall},
)