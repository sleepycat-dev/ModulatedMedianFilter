#include <string.h>

class CMedianFilter
{
protected:
	//data
	//read and write indexes
	int m_nWriteIndex;
	int m_nBufferSize;
	//array to hold samples to be sorted
	float * m_pSampleArray;

	//functions
	void reset();
	void resize(int nNewSize);
	//find median value and return it
	void doSwap(int nIndex1, int nIndex2);
	int doPartition(int nLow,int nHigh);
	float doSelectionAlgr(int nLeft,int nRight,int nMid);
	float getMedian();

public:
	CMedianFilter(int m_nBufferSize = 5);
	~CMedianFilter();
	void prepareForPlay();
	void processAudio(float & fInput);
	void setBufferSize(int nBufferSize);
};