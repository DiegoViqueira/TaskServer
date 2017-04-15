# TaskServer
c++ Task service

@Autor: Diego Viqueira
@Date: Nov - 2016

- Required : 
  - Boost Framework
    * Download the lastest version of Boost and install in GitHub root repository.
    
      Windows e.g:
        - b2  install architecture=x86  address-model=64 --prefix=C:\Boost --exec-prefix=_64 --libdir=C:\Boost\x64\lib --includedir=C:\Boost\x64\inlcude --build-dir=C:\Boost_64 
        - b2  install architecture=x86  address-model=32 --prefix=C:\Boost --exec-prefix=_32 --libdir=C:\Boost\x32\lib --includedir=C:\Boost\x32\inlcude --build-dir=C:\Boost_32 
     
	    Linux e.g:
	      -
	- IMPORTANT: Change in Vs project the includes dir for boost.
	 
  - Utils (https://github.com/DiegoViqueira/Utils)
