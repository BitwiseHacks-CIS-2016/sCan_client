from distutils.core import setup

setup(
    name='pScan_client',
    author='Daniel Hsing',
    description='Command Line utility for creating/update sCan devices',
    version='0.0.1',
    author_email='hsing.daniel@gmail.com',
    py_modules=['client'],
    install_required=[
        'click',
        'clint',
        'requests'
    ],
    entry_points = {
        'console_scripts': 'sCan = client:main'
    }
)