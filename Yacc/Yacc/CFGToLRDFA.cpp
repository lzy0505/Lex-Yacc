#include "stdafx.h"
#include "structs.h"

//TODO £∫¡ı
static void epsilon_clousure(const int boundTInt, const int boundNInt, const ProducerMuiltiMap &producerMuiltiMap, unordered_set<LRItem> &lrStateSet);
static bool subset_construct(const int boundTInt, const int boundNInt, const ProducerVec & ProducerVec,const unordered_set<LRItem> &lrStateSet, const string& edge,unordered_set<LRItem> &newSet);


void cfg_to_lrdfa(const int boundTInt, const int boundNInt, const string &start, const ProducerVec & ProducerVec, const ProducerMuiltiMap &producerMuiltiMap, LRDFA & lrdfa) {
	
}

void epsilon_clousure(const int boundTInt, const int boundNInt, const ProducerMuiltiMap &producerMuiltiMap, unordered_set<LRItem> &lrStateSet) {

}


bool subset_construct(const int boundTInt, const int boundNInt, const ProducerVec & ProducerVec, const unordered_set<LRItem> &lrStateSet, const string& edge, unordered_set<LRItem> &newSet) {

}