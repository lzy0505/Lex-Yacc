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
vector<unordered_set<int>> leftAssociativeVec;//�ƽ���Լ��

void lrdfa_to_table(const LRDFA &lrdfa ,int *& next_state, int *& reduce_state) {
	//base��ͨ��״̬�ŵõ���Ӧһά���������λ�á�
	int* base = new int[boundNInt+2];
	memset(base,0, (boundNInt + 2) * sizeof(int));
	//nextͨ��base���ֵ+�ս���߷��ս��ȡֵ�õ���һ״̬
	int* next = new int[(boundNInt + 2)*lrdfa.statesVec.size()];
	memset(next, -1, (boundNInt + 2)*lrdfa.statesVec.size() * sizeof(int));//-1��ʾ����
	int* shift_reduce = new int[(boundNInt + 2)*lrdfa.statesVec.size()];
	memset(shift_reduce, -2, (boundNInt + 2)*lrdfa.statesVec.size() * sizeof(int));//-2��ʾ����-1��ʾ��Լ��0��ʾɶ��û�У�1��ʾ�ƽ�


	//��������״̬����
	for (int i = 0; i < lrdfa.statesVec.size(); ++i) {
		base[lrdfa.statesVec[i].numberInt] = i * (boundNInt + 1);//�൱���к�
		//��ÿ��״̬�����൱�ڶ�ÿһ�д���

		//�Ȱ��ƽ��ͷ��ս������������ˣ����������
		for (auto j = lrdfa.statesVec[i].edgesMap.begin(); j != lrdfa.statesVec[i].edgesMap.end();j++) {
			if (j->first <= boundTInt) {//�ս��
					next[base[lrdfa.statesVec[i].numberInt] + j->first] = j->second;//��ֵ��һ��״̬
					//�ƽ�
					shift_reduce[base[lrdfa.statesVec[i].numberInt] + j->first] = 1;
			}
			else if (j->first == -2) {//��$
				next[base[lrdfa.statesVec[i].numberInt] + boundTInt+1] = j->second;//��ֵ��һ��״̬
				//�ս������Լ��
				shift_reduce[base[lrdfa.statesVec[i].numberInt] + boundTInt + 1] = -1;
			}
			else {//���ս��
				next[base[lrdfa.statesVec[i].numberInt] + j->first] = j->second;//��ֵ��һ��״̬
				shift_reduce[base[lrdfa.statesVec[i].numberInt] + j->first] = 0;
			}
		}

		//�������Ź�Լ���,��״̬�е�ÿһ����ʽ���в���
		for (auto it = lrdfa.statesVec[i].LRItemsSet.begin(); it != lrdfa.statesVec[i].LRItemsSet.end();it++) {
			//����ǵ������������й�Լ
			if (it->positionInt == producerVec[it->gramarInt].second.size()) {
					//ȡ��Ԥ���������Ԥ������������ս�������û��shift_reduce[i]=0�����
					//����ƽ���Լ��ͻ
					if (shift_reduce[base[lrdfa.statesVec[i].numberInt] + it->predictiveSymbol] == 1) {
						int preLine = -1,lastLine=-1;//preLine��¼Ԥ�����������lastLine��¼ÿ�����һ���ս��������������Խ�����ȼ�Խ�ߣ�ͬһ�а��������������ͻ
						//�ҵ�����ʽ�����һ���ս��
						int last;
						for (last = producerVec[it->gramarInt].second.size() - 1; last >= 0; last--) {
							//С������������ս��
							if (last <= boundTInt) break;
						}
						//�ڹ�����ж�λԤ�����last�ս��
						for (int i = 0; i < leftAssociativeVec.size(); ++i) {
							for (auto j = leftAssociativeVec[i].begin(); j != leftAssociativeVec[i].end(); j++) {
								//�ҵ�Ԥ���
								if (*j == it->predictiveSymbol) {
									preLine = i;//��¼���ȼ�
								}//�ҵ����һ���ս��
								else if(last==*j){
									lastLine = i;//��¼���ȼ�
								}
							}
						}
						//����й��򣬰��չ�����,û�о����ƽ���ɶ��������
						if (preLine!=-1&&lastLine!=-1) {
							//���һ�����ս�����ȼ���,��Ϊ��Լ����֮�����ƽ������Ѿ�ʲô����������
							if (preLine <= lastLine) {
								next[base[lrdfa.statesVec[i].numberInt] + it->predictiveSymbol] = it->gramarInt;
								shift_reduce[base[lrdfa.statesVec[i].numberInt] + it->predictiveSymbol] == -1;//��Լ
							}
						}
					}//�����Լ��Լ��ͻ
					else if (shift_reduce[base[lrdfa.statesVec[i].numberInt] + it->predictiveSymbol] == -1) {
						//�Ƚϲ���ʽ���ȼ���ѡ�����ȼ��ߣ�����Ƚ�С�ģ�������Լ
						if (next[base[lrdfa.statesVec[i].numberInt] + it->predictiveSymbol] > it->gramarInt) {
							next[base[lrdfa.statesVec[i].numberInt] + it->predictiveSymbol] = it->gramarInt;
						}
					}
					else {//û�г�ͻ����Ѳ���ʽ��Ӧ�ı�Ÿ�ֵ��
						next[base[lrdfa.statesVec[i].numberInt] + it->predictiveSymbol] = it->gramarInt;
						shift_reduce[base[lrdfa.statesVec[i].numberInt] + it->predictiveSymbol] == -1;//��Լ
					}		
			}
		}
	}
}
