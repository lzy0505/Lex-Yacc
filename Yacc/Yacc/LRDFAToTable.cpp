#include"stdafx.h"
#include"structs.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::pair;
// TODO : ��ĳ
// next_state[] ��ת����һ��״̬
// reduce_state[] �Ƿ���Ҫ��Լ,ע�����⴦��$-r0
extern int boundNInt;
extern int boundTInt;
extern ProducerVec producerVec;//���ڱ���±�Ѱַ
extern vector<string> &leftAssociativeVec;//�ƽ���Լ��

void lrdfa_to_table(const LRDFA &lrdfa ,int *& next_state, int *& reduce_state) {
//	//base��ͨ��״̬�ŵõ���Ӧһά���������λ�á�
//	int* base = new int[boundNInt+2];
//	memset(base,0, (boundNInt + 2) * sizeof(int));
//	//nextͨ��base���ֵ+�ս���߷��ս��ȡֵ�õ���һ״̬
//	int* next = new int[(boundNInt + 2)*lrdfa.statesVec.size()];
//	memset(next, -1, (boundNInt + 2)*lrdfa.statesVec.size() * sizeof(int));//-1��ʾ����
//	int* shift_reduce = new int[(boundNInt + 2)*lrdfa.statesVec.size()];
//	memset(shift_reduce, -2, (boundNInt + 2)*lrdfa.statesVec.size() * sizeof(int));//-2��ʾ����-1��ʾ��Լ��0��ʾɶ��û�У�1��ʾ�ƽ�
//
//
//	//��������״̬����
//	for (int i = 0; i < lrdfa.statesVec.size(); ++i) {
//		base[lrdfa.statesVec[i].numberInt] = i * (boundNInt + 1);//�൱���к�
//		//��ÿ��״̬�����൱�ڶ�ÿһ�д���
//
//		//�Ȱ��ƽ��ͷ��ս�������������
//		for (auto j = lrdfa.statesVec[i].edgesMap.begin(); j != lrdfa.statesVec[i].edgesMap.end();j++) {
//			if (j->first <= boundTInt) {//�ս��
//					next[base[lrdfa.statesVec[i].numberInt] + j->first] = j->second;//��ֵ����һ��״̬
//					//�ƽ�
//					shift_reduce[base[lrdfa.statesVec[i].numberInt] + j->first] = 1;
//			}
//			else if (j->first == -2) {//��$
//				next[base[lrdfa.statesVec[i].numberInt] + boundTInt+1] = j->second;//��ֵ����һ��״̬
//				//�ս������Լ��
//				shift_reduce[base[lrdfa.statesVec[i].numberInt] + boundTInt + 1] = -1;
//			}
//			else {//���ս��
//				next[base[lrdfa.statesVec[i].numberInt] + j->first] = j->second;//��ֵ����һ��״̬
//				shift_reduce[base[lrdfa.statesVec[i].numberInt] + j->first] = 0;
//			}
//		}
//
//		//�������Ź�Լ���,��״̬�е�ÿһ����ʽ���в���
//		for (auto it = lrdfa.statesVec[i].LRItemsSet.begin(); it != lrdfa.statesVec[i].LRItemsSet.end();it++) {
//			//��������һ��
//			if (it->positionInt == producerVec[it->gramarInt].second.size()) {
//				//ȡ��Ԥ�������
//				for (auto pre = it->predictiveItemSet.begin(); pre != it->predictiveItemSet.end(); pre++) {
//					//TODO:����ƽ���Լ��ͻ
//					if (shift_reduce[base[lrdfa.statesVec[i].numberInt] + *pre] == 1) {
//
//					}
//					else if (shift_reduce[base[lrdfa.statesVec[i].numberInt] + *pre] == -1) {//TODO:�����Լ��Լ��ͻ
//
//					}
//					else {
//						//ֻ�й�Լ����Ѳ���ʽ��Ӧ�ı�Ÿ�ֵ��
//						next[base[lrdfa.statesVec[i].numberInt] + *pre] = it->gramarInt;
//						shift_reduce[base[lrdfa.statesVec[i].numberInt] + *pre] == -1;//��Լ
//					}
//					
//				}
//			}
//		}
//		
//
//	}
//
	
}


//void resolve_conflicts(const vector<string> &leftAssociativeVec) {
//
//}