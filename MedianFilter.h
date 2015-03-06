#include <string.h>
#include "pluginconstants.h"

class CMedianFilter
{
protected:
	//data
	//read and write indexes
	int m_nWriteIndex;
	int m_nBufferSize;
	int m_nReadLimit;
	//previous output for interpolation
	float m_fPrevOut;
	//array to hold samples to be sorted
	float * m_pSampleArray;
	//Modulation
	//Accept?
	bool m_bExtModulation;
	//Destination
	UINT m_uModDest;
	enum{read,size};
	//height
	bool m_bPolarity;

	//functions
	void reset();
	void resize(int nNewSize);
	//find median value and return it
	void doSwap(int nIndex1, int nIndex2);
	int doPartition(int nLow,int nHigh);
	float doSelectionAlgr(int nLeft,int nRight,int nMid);
	float getMedian();
	float getModMedian(float fModVal);
	int getModReadLimit(float fModVal);

public:
	CMedianFilter(int nBufferSize = 5);
	~CMedianFilter();
	void prepareForPlay();
	void processAudio(float & fInput, float & fOut, float fModVal = 0.0);
	void setBufferSize(int nBufferSize);
	void setExtModulation(bool bExtMod);
	bool getExtModulation();
	void setPolarity(bool bPolarity);
	void setReadLimit(int nReadLimit);
	void setModDest(UINT uModDest);
};