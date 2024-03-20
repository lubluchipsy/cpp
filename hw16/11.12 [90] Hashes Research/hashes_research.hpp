#include <iostream>
#include <vector>
#include <random>
#include <unordered_set>
#pragma once


std::unordered_set <std::string> random_strings(std::size_t size, std::size_t number);


unsigned int RSHash(const char* str, unsigned int length);


unsigned int JSHash(const char* str, unsigned int length);


unsigned int ELFHash(const char* str, unsigned int length);


unsigned int PJWHash(const char* str, unsigned int length);


unsigned int BKDRHash(const char* str, unsigned int length);


unsigned int SDBMHash(const char* str, unsigned int length);


unsigned int DJBHash(const char* str, unsigned int length);


unsigned int DEKHash(const char* str, unsigned int length);


unsigned int APHash(const char* str, unsigned int length);
