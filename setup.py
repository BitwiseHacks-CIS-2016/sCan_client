from setuptools import setup

setup(
	name='sCan_client',
	author='Daniel Hsing',
	description='Script that creates, updates and deletes devices for the sCan webapp',
	version='0.0.2',
	license='MIT',
	url='https://github.com/BitwiseHacks-CIS-2016/sCan_client',
	py_modules=['client'],
	install_requires=[
		'click',
		'clint',
		'requests'
	],
	entry_points={
	    'console_scripts': [
	        'sCan=client:main',
	    ],
	}
)