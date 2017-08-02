/*
 * main.cpp
 *
 *  Created on: Aug 1, 2017
 *      Author: tomas1
 */

#include <stdio.h>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "myenergy.h"

static auto rtObj = myenergyModelClass();

int main(int argc, char **argv) {
	rtObj.initialize();

	auto buf = std::vector<char>(1632);
	auto buf1 = std::vector<char>(1504);
	std::cerr << "Descrambler..." << std::endl;

	while (!feof(stdin)) {
		auto count = 0;
		do {
			count += read(STDIN_FILENO, buf.data() + count, buf.size() - count);
		} while (count != buf.size());
		auto it { 0 };
		for (auto c : buf) {
			rtObj.rtU.In1[it++] = c;
		}
		rtObj.step();
		std::copy(rtObj.rtY.Out1, rtObj.rtY.Out1 + sizeof(rtObj.rtY.Out1),
				begin(buf1));
		if (write(STDOUT_FILENO, buf1.data(), buf1.size()) < 0) {
			perror("write");
		}
	}

	std::cerr << "Exiting.." << std::endl;
	return 0;
}

