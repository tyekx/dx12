#include "Common.h"
#include <sstream>
#include <cstdlib>

void Egg::Internal::Assert(bool trueMeansOk, const char * msgOnFail) {
	if(!trueMeansOk) { MessageBoxA(NULL, msgOnFail, "Assertion failed!", MB_ICONSTOP | MB_OK); exit(-1); }
}

Egg::Internal::HResultTester::HResultTester(const char * msg, const char * file, int line) : Message{ msg }, File{ file }, Line{ line } { }

void Egg::Internal::HResultTester::operator<<(HRESULT hr) {
	if(FAILED(hr)) {
		std::ostringstream oss;
		oss << File << "(" << Line << "): " << Message;

		MessageBoxA(NULL, oss.str().c_str(), "Error!", MB_ICONSTOP | MB_OK);
		exit(-1);
	}
}
