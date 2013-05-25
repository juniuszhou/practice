//
//	demo.cpp
//	2004-05-06 by ShanLanshan
//
//	此程序用于测试神经元的库函数
//	它展示了怎样用这个库所生成的多层BP网络来求解宇称问题
//	在Visual Stduio 2003上编译通过，要注意启动运行时信息的支持

#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include "public/ann/neuron.h"
#include "public/ann/bp/bpneuron.h"
#include "public/prob.h"
#include "public/ann/annlib.h"
#include "public/ann/vec_container.h"
#include "public/ann/vector.h"
#include "public/ann/annfunc/annfunc.h"
#include "Windows.h"
#include <fstream>

using namespace ann;

int main()
{
	char s[1024];
	const char *file = "C:\\bpnet.txt";

	for (int i=0; i< 0; ++i) {
		std::cout << prob_get_range(0, 3) << " ";
	}
	//std::cin >> s;

	AnnLib annlib;
	if (!annlib.init()) {
		std::cout << "ann lib init failed\n";
		return -1;
	}

	AnnFuncGroup *fg;
	fg = annfunc_get("sign");
	assert(fg != NULL);

	AnnSampleSet ass("宇称5");

	{
		std::ofstream os;
		os.open("C:\\YC5.txt");
		if (os.is_open()) {
			os << ass;
		}
	}
	return 0;

	BPNet net;
	AnnVector vec_input, vec_output, vec_tutor;

	bool openfile = true;
	std::ifstream is;
	if (openfile)
		is.open(file);
	if (openfile && is.is_open()) {
		std::cout << "open file ok\n";
		net << is;
	} else {
		//assert(net.init("2 * 16 * 8 * 2 * 1"));
		char initstr[64];
		sprintf(initstr, "%d * %s * %d",
				ass.m_input_division,
				"100 * 16",
				ass.m_output_division);
		std::cout << "Init: " << initstr << std::endl;
		net.init(initstr);
		net.mutual_conn();
		prob_set_seed(0);
		net.random();
	}


	//net.set_output_func(annfunc_get("sech6"), 0);
	net.set_output_func(annfunc_get("sech6"), 1);
	net.set_output_func(annfunc_get("sin"), 2);
	//net.set_output_func(annfunc_get("sech6"), 3);
	net.set_output_func(annfunc_get("sech6_cache"));
	//net.set_output_func(annfunc_get("sech6"));
	//net.set_output_func(annfunc_get("sin"));

	vec_output.set_size(net.get_output_division());

	int right = 0, k = 0;
	time_t t1,t2;

	t1 = time(NULL);

	for (int m = 0; m < 1; ++m) {
		//net.random();
		right = 0;
		std::cout << m << std::endl;
		for (int i=400000; i>0; --i) {
			printf(".");
			ass.get_sample(&vec_input, &vec_tutor);
			net.set_input(&vec_input);
			net.convert();
			net.get_output(&vec_output);
			net.learn(&vec_tutor);
			fg->multi_main(vec_output.get_buffer(), vec_output.get_size(), NULL);
			vec_output.release_buffer();

			if (0 && (i % 100) == 0) {
				std::cout << i << std::endl;
				Sleep(10);
			}
			//if (i < 200)
			if (0)
			std::cout << "\n\nSample" << i << " " << vec_input << std::endl
				<< "tutor : " << vec_tutor << std::endl
				<< "output: " << vec_output << std::endl
				<< std::endl;
			k ++;
			if (vec_tutor == vec_output) {
				++right;
				if (right >= 600) break;
			} else {
				right = 0;
			}
		}
	}

	t2 = time(NULL);
	std::cout << static_cast<long>(t2 - t1) << "seconds passed\n";
	std::cout << "Get correct in step " << k << ", ok\n";

	std::ofstream fs;
	fs.open(file);
	fs << net;

	std::cin >> s;
	return 0;
}
