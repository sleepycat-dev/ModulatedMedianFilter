#include "MedianFilter.h"

CMedianFilter::CMedianFilter(int nBufferSize)
{
	m_nBufferSize = nBufferSize;
	m_nReadLimit = m_nBufferSize;
	m_bExtModulation = false;
	m_bPolarity = false;
	m_nWriteIndex = 0;
	m_fPrevOut = 0;
	m_pSampleArray = new float[m_nBufferSize + 1];
}

CMedianFilter::~CMedianFilter()
{
	if(m_pSampleArray)
		delete [] m_pSampleArray;
}

void CMedianFilter::prepareForPlay()
{
	// Add your code here:
	if(m_pSampleArray)
		delete [] m_pSampleArray;

	m_pSampleArray = new float[m_nBufferSize + 1];
	reset();
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
	if(m_nReadLimit == 0 || m_nReadLimit == 1)
		return m_pSampleArray[m_nReadLimit];

	return doSelectionAlgr(0, m_nReadLimit, m_nReadLimit/2);
}

float CMedianFilter::getModMedian(float fModVal)
{
	//safety check to make sure values are in
	//valid range
	if(fModVal > 1.0)
		fModVal = 1.0;
	else if(fModVal < -1.0)
		fModVal = -1.0;

	//unipolar case
	if(!m_bPolarity)
	{
		int nIndex = (int)(fModVal*(m_nBufferSize-1));
		return m_pSampleArray[nIndex];
	}
	//bipolar case
	else
	{
		//smallest value for fModVal is -1 so bias up by 1 to 
		//adjust into usable range. Then divide by 2 to handle
		//largest case (1 shifted up by 1 is 2, and so is invalid)
		int nIndex = (int)(((fModVal+1.0)/2.0)*(m_nBufferSize-1));
		return m_pSampleArray[nIndex];
	}
}

int CMedianFilter::getModReadLimit(float fModVal)
{
	//safety check to make sure values are in
	//valid range
	if(fModVal > 1.0)
		fModVal = 1.0;
	else if(fModVal < -1.0)
		fModVal = -1.0;

	//unipolar case
	if(!m_bPolarity)
		return (int)(fModVal*(m_nBufferSize-1));

	//bipolar case
	else
	{
		//smallest value for fModVal is -1 so bias up by 1 to 
		//adjust into usable range. Then divide by 2 to handle
		//largest case (1 shifted up by 1 is 2, and so is invalid)
		return (int)(((fModVal+1.0)/2.0)*(m_nBufferSize-1));
	}
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
}

void CMedianFilter::reset()
{
	if(m_pSampleArray)
		memset(m_pSampleArray, 0, m_nBufferSize*sizeof(float));
	m_nWriteIndex = 0;
}

void CMedianFilter::processAudio(float & fIn, float & fOut, float fModVal)
{
	m_pSampleArray[m_nWriteIndex] = fIn;
	float fMedian = 0.0;

	if(m_bExtModulation && m_uModDest == read)
		fMedian = getModMedian(fModVal);
	if(m_bExtModulation && m_uModDest == size)
	{
		m_nReadLimit = getModReadLimit(fModVal);
		fMedian = getMedian();
	}
	else
		fMedian = getMedian();

	//Interpolate between previous output and current output to reduce aliasing
	fOut = dLinTerp(0, 1, fMedian, m_fPrevOut, (float)1.0/44100.0);

	m_nWriteIndex++;
	if(m_nWriteIndex > m_nReadLimit)
		m_nWriteIndex = 0;	
	m_fPrevOut = fOut;
}

void CMedianFilter::setBufferSize(int nBufferSize)
{
	reset();
	m_nBufferSize = nBufferSize;
}

void CMedianFilter::setExtModulation(bool bExtMod)
{m_bExtModulation = bExtMod;}

void CMedianFilter::setPolarity(bool bPolarity)
{m_bPolarity = bPolarity;}

bool CMedianFilter::getExtModulation()
{return m_bExtModulation;}

void CMedianFilter::setReadLimit(int nReadLimit)
{m_nReadLimit = nReadLimit;}

void CMedianFilter::setModDest(UINT uModDest)
{m_uModDest = uModDest;}