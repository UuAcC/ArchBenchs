#include "tests.h"
#include "decomposer_lu.h"

// ----------------------------------------< workability tests >---------------------------------------------------

std::vector<WorkabilityTestPtr> TestSystem::workability_tests;

bool TestSystem::test_LU(SquareMatrix& A, std::string test_num, bool print_a, bool print_lu, bool print_res) {
	print_test_start(test_num);
	if (print_a) {
		printf("Matrix A:\n");
		A.out_with_printf();
		printf("\r\n");
	}
	const size_t n = A.get_size();
	SquareMatrix* LU = new SquareMatrix(A);
	DecomposerLU::block_get_LU(LU->get_array(), n);
	if (print_lu) {
		DecomposerLU::out_LU_with_printf(*LU);
	}
	SquareMatrix L(n), U(n);
	DecomposerLU::decompose_LU((*LU), L, U);
	delete LU; LU = nullptr;
	L *= U;
	double infinite_cond_A = (L - A).get_infinite_norm() /
		(A.get_infinite_norm() * SquareMatrix::mashine_eps);
	if (print_res) {
		printf("Matrix Res = L * U:\n");
		L.out_with_printf();
	}
	printf("\r\n");
	analyze_cond(infinite_cond_A);
	printf("\r\n");
	print_test_end(test_num);

	return A == L;
}

bool TestSystem::test1() {
	const size_t n = 3;
	Type arr[n * n]{
		2, 3, 1,
		4, 7, 7,
		6, 18, 22
	};
	SquareMatrix A(n, arr);
	return test_LU(A, "1", 1, 1, 1);
}

bool TestSystem::test2() {
	const size_t n = 4;
	Type arr[n * n]{
		2, 3, 1, 1,
		4, 7, 7, 1,
		6, 18, 22, 1,
		1, 1, 1, 1
	};
	SquareMatrix A(n, arr);
	return test_LU(A, "2", 1, 1, 1);
}

bool TestSystem::test3() {
	const size_t n = 4;
	SquareMatrix A(n, -1e6, 1e6);
	return test_LU(A, "3", 1, 1, 1);
}

bool TestSystem::test4() {
	const size_t n = 50;
	SquareMatrix A(n, -1e6, 1e6);
	return test_LU(A, "4");
}

// ----------------------------------------------------------------------------------------------------------------

// ----------------------------------------< time tests >----------------------------------------------------------

#ifndef TP
#define TP steady_clock::time_point 
#endif
#ifndef NOW
#define NOW steady_clock::now()
#endif

bool TestSystem::do_accuracy_check = true;
bool TestSystem::random_initialization = false;

#if defined REFERENCE_TEST && REFERENCE_TEST == eigen
ReturnedResults TestSystem::single_test_time(size_t n, size_t iter, SquareMatrix*& A) {
	ReturnedResults results;

	TP start_init = NOW;
	if (random_initialization) { A = new SquareMatrix(n, 1e-6, 1e6); }
	else { A = new SquareMatrix(n, true); }
	SquareMatrix LU(*A);

	results.InitTime = duration_cast<milliseconds>(NOW - start_init);

	TP start_LU = NOW;
	DecomposerLU::block_get_LU(LU.get_array(), n, n);
	results.LUTime = duration_cast<milliseconds>(NOW - start_LU);

	results.TotalTime = duration_cast<milliseconds>(NOW - start_init);

	if (do_accuracy_check) {
		SquareMatrix L(n), U(n);
		DecomposerLU::decompose_LU(LU, L, U);
		SquareMatrix Res = L * U;
		double infinite_cond_A = (Res - *A).get_infinite_norm() /
			(A->get_infinite_norm() * SquareMatrix::mashine_eps);

		results.is_correct = (*A == Res);

		printf("\n%u) ", iter + 1);
		analyze_cond(infinite_cond_A);
		printf(" Test result: %s. ", results.is_correct ? "true" : "false");
		printf("LU Time: %lld\n", results.LUTime.count());
	}
	else { results.is_correct = false; }
	return results;
}

#include <Eigen/Dense>      
#include <Eigen/LU>    
ReturnedResults TestSystem::single_reference_test(size_t n, size_t iter, const SquareMatrix& sqmtr) {
	ReturnedResults results;
	Eigen::MatrixXd A(n, n);
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			A(i, j) = sqmtr(i, j);
		}
	}

	TP start_LU = NOW;
	Eigen::PartialPivLU<Eigen::MatrixXd> lu(A);
	results.LUTime = duration_cast<milliseconds>(NOW - start_LU);

	if (do_accuracy_check) {
		Eigen::MatrixXd L = Eigen::MatrixXd::Identity(n, n);
		L.triangularView<Eigen::StrictlyLower>() = lu.matrixLU();
		Eigen::MatrixXd U = lu.matrixLU().triangularView<Eigen::Upper>();
		Eigen::MatrixXd P = lu.permutationP();
		Eigen::MatrixXd A_reconstructed = P.inverse() * L * U;

		double error = (A - A_reconstructed).norm();

		results.is_correct = error < SquareMatrix::mashine_eps;

		printf("   Reference test %u. ", iter + 1);
		printf("LU Time: %lld. ", results.LUTime.count());
		printf(" Test result: %s.\n", results.is_correct ? "true" : "false");
	}
	else { results.is_correct = false; }
	return results;
}

#else

ReturnedResults TestSystem::single_test_time(size_t _n, size_t iter, bool huge_divided) {
	ReturnedResults results;
	size_t n = _n, hdt = 1;
	if (huge_divided) { hdt = _n * _n / 2500; n = 50; }
	microseconds inittime{ 0 }, lutime{ 0 }, totaltime{ 0 };
	for (size_t i = 0; i < hdt; ++i) {
		TP start_init = NOW;

		SquareMatrix A(n);
		if (random_initialization) { A = SquareMatrix(n, 1e-6, 1e6); }
		else { A = SquareMatrix(n, true); }
		SquareMatrix* LU = new SquareMatrix(A);

		inittime += duration_cast<microseconds>(NOW - start_init);

		TP start_LU = NOW;
		DecomposerLU::block_get_LU(LU->get_array(), n);
		lutime += duration_cast<microseconds>(NOW - start_LU);

		totaltime += duration_cast<microseconds>(NOW - start_init);

		if (do_accuracy_check) {
			SquareMatrix L(n), U(n);
			DecomposerLU::decompose_LU((*LU), L, U);
			delete LU; LU = nullptr;
			L *= U;
			results.is_correct &= (A == L);
			if (!huge_divided) {
				double infinite_cond_A = (L - A).get_infinite_norm() /
					(A.get_infinite_norm() * SquareMatrix::mashine_eps);
				printf("\n%u) ", iter + 1);
				analyze_cond(infinite_cond_A);
				printf(" Test result: %s. ", results.is_correct ? "true" : "false");
				printf("LU Time: %s\n", to_string(lutime.count()).c_str());
			}
		}
		else { 
			delete LU; LU = nullptr;
			results.is_correct = false; 
		}
	}
	results.InitTime = duration_cast<milliseconds>(inittime);
	results.LUTime = duration_cast<milliseconds>(lutime);
	results.TotalTime = duration_cast<milliseconds>(totaltime);
	if (huge_divided && do_accuracy_check) {
		printf("\n%u) [ Infinite cond(A) unsupported for huge matrices ]", iter + 1);
		printf(" Test result: %s. ", results.is_correct ? "true" : "false");
		printf("LU Time: %s\n", to_string(results.LUTime.count()).c_str());
	}
	return results;
}
#endif

void TestSystem::test_time(size_t _n, size_t how_many_times) {
	print_test_start("time");
	chrono::milliseconds time_init{ 1000000000 }, total_time{ 1000000000 }, time_LU{ 1000000000 };
#if defined REFERENCE_TEST && REFERENCE_TEST == eigen
	chrono::milliseconds time_LU_ref{ 1000000000 };
#endif
	printf("Testing with n = %u, ", _n); 
	printf("%u", how_many_times); printf(" times:\n");
	const size_t MAXSZ = (do_accuracy_check) ? 70 : 80;
	bool huge_divided = _n > MAXSZ && _n % 50 == 0;
	if (_n > MAXSZ && !huge_divided) {
		printf("FATAL ERROR: Can't run due to insufficient RAM! Run time test with another matrix size.\n");
		printf("             Max: 70 in normal and 80 with --dac. Sizes in multiples of 50 are also supported (WIP).");
		printf("\n-------------------------------------------------------------------------------------------------\n");
		return;
	}
	double cc = 0, incc = 0;
	for (size_t iter = 0; iter < how_many_times; ++iter) {
#if defined REFERENCE_TEST && REFERENCE_TEST == eigen
		SquareMatrix* A = new SquareMatrix(n);
		ReturnedResults res = single_test_time(n, iter, A);
#else
		ReturnedResults res = single_test_time(_n, iter, huge_divided);
#endif
		time_init = (time_init > res.InitTime) ? res.InitTime : time_init;
		time_LU = (time_LU > res.LUTime) ? res.LUTime : time_LU;
		total_time = (total_time > res.TotalTime) ? res.TotalTime : total_time;
		if (do_accuracy_check) {
			if (res.is_correct) { ++cc; }
			else { ++incc; }
		}
#if defined REFERENCE_TEST && REFERENCE_TEST == eigen
		ReturnedResults resref = single_reference_test(n, iter, *A);
		time_LU_ref = (time_LU_ref > resref.LUTime) ? resref.LUTime : time_LU_ref;
#endif
	}
	printf("\nMinimum time for init random matrix: ");
	string otpt = to_string(time_init.count());
	printf("%s", otpt.c_str());

	printf(" ms\nMinimum time for LU decomposition: ");
	otpt = to_string(time_LU.count());
	printf("%s", otpt.c_str());
#if defined REFERENCE_TEST && REFERENCE_TEST == eigen
	printf(" ms\nMinimum time for reference LU decomposition: ");
	otpt = to_string(time_LU_ref.count());
	printf("%s", otpt.c_str());
#endif
	printf(" ms\nMinimum total time: ");
	otpt = to_string(total_time.count());
	printf("%s", otpt.c_str());

	if (do_accuracy_check) {
		printf(" ms\n\nTotal test result: "); printf("%2f", cc / (cc + incc) * 100);
		printf("%\nCorrect count: "); printf("%2f", cc);
		printf("\nIncorrect count: "); printf("%2f", incc);
	}
	printf("\n-------------------------------------------------------------------------------------------------\n");
}

// ----------------------------------------------------------------------------------------------------------------

// ----------------------------------------< printing >------------------------------------------------------------

void TestSystem::print_test_start(std::string s) {
	printf("\n------------------------------------------- Test %s -------------------------------------------\n", 
		s.c_str());
}

void TestSystem::print_test_end(std::string s) {
	printf("----------------------------------------------------------------------------------------------\nTest %s: ", 
		s.c_str());
}

// ----------------------------------------------------------------------------------------------------------------

// ----------------------------------------< other functions >----------------------------------------------------

void TestSystem::enable_workability_tests() {
	workability_tests.push_back(TestSystem::test1);
	workability_tests.push_back(TestSystem::test2);
	workability_tests.push_back(TestSystem::test3);
	workability_tests.push_back(TestSystem::test4);
}

void TestSystem::disable_accuracy_check() { do_accuracy_check = false; }

void TestSystem::enable_random_initialization() { random_initialization = true; }

static void print_requires(size_t mtxsz, size_t MAXSZ) {
	const size_t tpsz = sizeof(Type);
	const size_t reqsz = (mtxsz > 50 && !(mtxsz > MAXSZ && mtxsz % 50 == 0)) ? mtxsz : 50;
	double result = (double)(reqsz * reqsz * tpsz * 3);
	char* val = getenv("OMP_NUM_THREADS");
	int threads = (val) ? atoi(val) : 0;
	result += (double)(tpsz * reqsz * threads);
#if defined REFERENCE_TEST && REFERENCE_TEST == eigen
	result += (double)(reqsz * reqsz * tpsz);
#endif
	int i = 0;
	for (; i < 3; ++i) {
		if (result < 500.0) break;
		result /= 1024.0;
	}
	printf("Requires >= %3f %s of RAM\n", result, 
		(i == 0) ? "bytes" : ((i == 1) ? "Kb" : ((i == 2) ? "Mb" : "Gb")));
}
void TestSystem::run_all_tests(size_t n, size_t count, std::string filename) {
	printf("TestSystem:\nTesting with values type: %s\n", typeid(Type).name());
#if defined REFERENCE_TEST && REFERENCE_TEST == eigen
	printf("Reference test library: Eigen 5.0.0");
#endif
	print_requires(n, (do_accuracy_check) ? 70 : 80);
	bool last_res;
	for (auto TestPtr : workability_tests) {
		last_res = (*TestPtr)();
		printf("%s", (last_res) ? "true\n\n" : "false\n\n");
	}
	test_time(n, count);
	do_accuracy_check = true;
	random_initialization = false;
	workability_tests.clear();
}

enum cond_quality { good, ill, singular };
void TestSystem::analyze_cond(double cond) {
	printf("Infinite cond(A): "); printf("%f; ", cond);
	cond_quality cq;
	if (cond < 1e+3) { cq = cond_quality::good; }
	else {
		if (cond >= 1e+3 && cond <= 1e+6) { cq = cond_quality::ill; }
		else { cq = cond_quality::singular; }
	}
	switch (cq) {
	case cond_quality::good:
		printf("Matrix is good-conditioned."); break;
	case cond_quality::ill:
		printf("WARNING! Matrix is ill-conditioned."); break;
	case cond_quality::singular:
		printf("CRITICAL! Matrix is singular-conditioned!"); break;
	}
}

// ----------------------------------------------------------------------------------------------------------------
