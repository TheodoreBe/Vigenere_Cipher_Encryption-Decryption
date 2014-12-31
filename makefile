CXX=g++
all: crypto_cracker crypto
crypto_cracker: crypto_cracker.cpp
	$(CXX) crypto_cracker.cpp -o crypto_cracker
crypto: crypto.cpp
	$(CXX) crypto.cpp -o crypto
clean: 
	rm -f  crypto_cracker crypto