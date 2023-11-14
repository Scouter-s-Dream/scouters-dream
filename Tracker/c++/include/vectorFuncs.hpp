#ifndef __printVector__HPP
#define __printVector__HPP

#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include <vector>

using std::vector;

std::vector<vector<int>> vector1Dto2D(std::vector<int> input, std::vector<size_t> newShape);

#endif