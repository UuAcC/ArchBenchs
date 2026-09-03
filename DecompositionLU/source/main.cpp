#include "tests.h"
#include <iostream>
#include <typeinfo> 

extern "C" {
	#include "retarget.h"
	#include <system_k1921vg1t.h>
	void trng_init(void);
}

using namespace std;

int main()
{
	SystemInit();
	SystemCoreClockUpdate();
	retarget_init();
	trng_init();
	
	int argc = 0;
	string argv[15], input;
	printf("Enter command line without programm name (args):\n");

	const size_t BUFFER_SIZE = 256;
	input.resize(BUFFER_SIZE);
	if (fgets(&input[0], BUFFER_SIZE, stdin) != nullptr) {
		size_t len = std::strlen(input.c_str());
		if (len > 0 && input[len - 1] == '\n')
			--len;
		input.resize(len);
	}
	int i = 0;
	string buff = "";
	while (input[i] != '\0') {
		if (input[i] != ' ') { buff += input[i]; }
		else if (!buff.empty()) {
			argv[argc] = buff; ++argc;
			buff.clear();
		}
		++i;
	}
	if (!buff.empty()) {
		argv[argc] = buff; ++argc;
		buff.clear();
	}

	string fname; 
	size_t size, count;
	bool hsz = false, hcnt = false;
	for (int i = 0; i < argc; ++i) {
		const char* arg = argv[i].c_str();
		if (strcmp(arg, "--help") == 0) {
			printf("CMD Options:\n");
			printf("  --help					Show help.\n");
			printf("  --size [VALUE]				Set size of matrix used in time tests equal to VALUE.\n");
			printf("  --count [VALUE]				Program do the time test VALUE times (new matrix every time).\n");
			printf("  --out [PATH]					All the program output will be write in file [PATH] (.txt file).\n");
			printf("  --workability_tests (--wt)			Enables workability tests.\n");
			printf("  --disable_accuracy_check (--dac)		Disables result checking in time-measuring tests.\n");
			printf("  --random_initialization (--ri)		Enables random matrix initialization (in range [1e-6; 1e6]).\n");
			printf("Compilation options:\n");
			printf("  -DLU_BLOCK_SIZE=[VALUE]				Set size of block used in block LU algorithm (default 64).\n");
			printf("  -DPRINT_BLOCK_TIMES=1				Enables measuring part's times of block LU algorithm:\n");
			printf("							L11xU11: A11 -> L11 and U11;\n");
			printf("							L21: A21->L21;\n");
			printf("							U12: A12->U12;\n");
			printf("							L22xU22: A22->L22* U22.\n");
			printf("  -DREFERENCE_TEST=[ eigen | mkl ]		Set library to compare results with. Works with exactly same matrixes.\n");
			printf("  -DTYPE=[int, float, double, etc.]		Set type of values in matrixes.\n");
			return 0;
		}
		else if (strcmp(arg, "--size") == 0 && i + 1 < argc) {
			size = stoull(argv[i + 1]); hsz = true; ++i;
		}
		else if (strcmp(arg, "--count") == 0 && i + 1 < argc){
			count = stoull(argv[i + 1]); hcnt = true; ++i;
		}
		else if (strcmp(arg, "--out") == 0 && i + 1 < argc) {
			fname = arg; ++i;
		}
		else if (strcmp(arg, "--wt") == 0 ||
			strcmp(arg, "--workability_tests") == 0)
		{
			TestSystem::enable_workability_tests();
		}
		else if (strcmp(arg, "--dac") == 0 ||
			strcmp(arg, "--disable_accuracy_check") == 0)
		{
			TestSystem::disable_accuracy_check();
		}
		else if (strcmp(arg, "--ri") == 0 ||
			strcmp(arg, "--random_initialization"))
		{
			TestSystem::enable_random_initialization();
		}
	}
	printf("Use \"--help\" to see additional options.\n\n");
	size_t arg1 = (hsz) ? size : 10;
	size_t arg2 = (hcnt) ? count : 1;

	TestSystem::run_all_tests(arg1, arg2, fname);

	while (1) {}

	return 0; 
}
