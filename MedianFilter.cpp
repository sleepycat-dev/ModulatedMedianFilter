#include "MedianFilter.h"

void CMedianFilter::prepareForPlay()
{
	// Add your code here:
	if(m_pSampleArray)
		delete [] m_pSampleArray;

	m_pSampleArray = new float[m_nBufferSize + 1];
}

void CMedianFilter::doSwap(int nIndex1, int nIndex2)
{
	float fTemp = m_pSampleArray[nIndex1];
	m_pSampleArray[nIndex1] = m_pSampleArray[nIndex2];
	m_pSampleArray[nIndex2] = fTemp;
}

int CMedianFilter::doPartition(int nLow,int nHigh)
{
    int p = nLow;
	int r = nHigh;
	float fTemp = m_pSampleArray[r];
	int i = p-1;

    for(int j = p; j <= r-1; j++)
    {
		if (m_pSampleArray[j] <= fTemp)
        {
            i=i+1;
            doSwap(i,j);
        }
    }
    doSwap(i+1,r);
    return i+1;
}

float CMedianFilter::doSelectionAlgr(int nLeft,int nRight,int nMid)
{
    while(true)
    {
        int nPivotIndex = doPartition(nLeft,nRight);          //Select the Pivot Between Left and Right
        int nLen = nPivotIndex-nLeft+1;

        if(nMid == nLen)
			return m_pSampleArray[nPivotIndex];

        else if(nMid < nLen)
            nRight = nPivotIndex - 1;

        else
        {
            nMid = nMid - nLen;
            nLeft = nPivotIndex + 1;
        }
    }
}

float CMedianFilter::getMedian()
{
	//call selection algorithm http://discuss.codechef.com/questions/1489/find-median-in-an-unsorted-array-without-sorting-it
	if(m_nBufferSize == 1)
		return m_pSampleArray[0];

	return doSelectionAlgr(0, m_nBufferSize, m_nBufferSize/2);
}

void CMedianFilter::resize(int nNewSize)
{
	//make array of new size, copy over contents, delete old array, copy over to pointer
	float * fTemp = new float[nNewSize + 1];
	if(m_pSampleArray)
	{
		if(m_nBufferSize < nNewSize)
		{
			for(int i = 0; i < m_nBufferSize; i++)
				fTemp[i] = m_pSampleArray[i];
		}
		else
		{
			for(int i = 0; i < nNewSize; i++)
				fTemp[i] = m_pSampleArray[i];
		}
		for(int j = m_nBufferSize; j < nNewSize; j++)
			fTemp[j] = 0;
		delete [] m_pSampleArray;
	}
	m_pSampleArray = fTemp;
	m_nBufferSize = nNewSize;
}

void CMedianFilter::reset()
{
	if(m_pSampleArray)
		memset(m_pSampleArray, 0, m_nBufferSize*sizeof(float));
	m_nWriteIndex = 0;
}