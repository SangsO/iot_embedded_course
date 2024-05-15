#pragma once
#include <Windows.h>
#include <assert.h>
#include <cstdio>
#define CLIP(x) (x < 0) ? 0 : x > 255 ? 255 : x //아주 많은 데이터들을(바이트데이터)를 엑세스 해야해서

template <typename T> //클래스 이름 또는 템플릿 이름 적어주면 됨

class CMyImage
{
public:
	CMyImage(void)
		: m_nChannels(0)
		, m_nHeight(0)
		, m_nWidth(0)
		, m_nWStep(0)
		, m_pImageData(NULL)
	{
	}

	CMyImage(int nWidth, int nHeight, int nChannels = 1) //채널은 기본으로 지정해줌(default 매개변수)
		:m_nChannels(nChannels)
		, m_nHeight(nHeight)
		, m_nWidth(nWidth)
		, m_nWStep(((nWidth* nChannels * sizeof(T) + 3) & ~3) / sizeof(T)) //동적 할당
	{
		m_pImageData = new T[m_nHeight * m_nWStep];
	}

	CMyImage(const CMyImage& myImage) //매개변수를 자기자신 참조변수로 받는 복사생성자
	{
		m_nChannels = myImage.m_nChannels;
		m_nHeight = myImage.m_nHeight;
		m_nWidth = myImage.m_nWidth;
		m_nWStep = myImage.m_nWStep;
		m_pImageData = new T[m_nHeight * m_nWStep]; //동적할당 사용 -> 깊은복사
		memcpy(m_pImageData, myImage.m_pImageData, m_nHeight * m_nWStep * sizeof(T));
	}

	CMyImage& operator = (const CMyImage& myImage) //operator -> 연산자 중복정의 (대입 연산자에 대한 내용)
	{
		if (this == &myImage) //우측에 있는 데이터를 좌측에 집어넣을 때
			return *this; //자기 자신이면 자기자신의 주소를 리턴

		m_nChannels = myImage.m_nChannels;
		m_nHeight = myImage.m_nHeight;
		m_nWidth = myImage.m_nWidth;
		m_nWStep = myImage.m_nWStep;

		if (m_pImageData)
			delete[] m_pImageData;
		if (myImage.m_pImageData != NULL)
		{
			m_pImageData = new T[m_nHeight * m_nWStep];
			memcpy(m_pImageData, myImage.m_pImageData, m_nHeight * m_nWStep * sizeof(T));
		}
		return *this;
	}
	template <typename From>
	CMyImage(const CMyImage<From>& myImage) // 바이트가 아닐 때 사용하려고 한 거 같음
	{
		m_nChannels = myImage.GetChannel();
		m_nHeight = myImage.GetHeight();
		m_nWidth = myImage.GetWidth();
		m_nWStep = ((m_nWidth * m_nChannels * sizeof(T) + 3) & ~3) / sizeof(T);
		m_pImageData = new T[m_nHeight * m_nWStep];

		int nWStep = myImage.GetWStep();

		if (sizeof(T) == 1)
		{
			for (int r = 0; r < m_nHeight; r++)
			{
				T* pDst = GetPtr(r);	//복사할 위치 주소값 ->row의 인덱스를 받아 해당하는 주소값 리턴
				From* pSrc = myImage.GetPtr(r); // 원본에 대한 이미지
				for (int c = 0; 0 < nWStep; c++)
				{
					pDst[c] = (T)(pSrc[c]); //4의 배수가 아니면 4의배수로 만들어서 저장한다는 명령
				}
			}
		}
	}

	~CMyImage(void)
	{
		if (m_pImageData) delete[] m_pImageData;
	}

	bool LoadImage(const char* filename) //이미지 읽어오는 부분
	{
		assert(sizeof(T) == 1); // BYTE형의 경우만 가능

		if (! strcmp(".BMP", &filename[strlen(filename) - 4]))
		{
			FILE* pFile = NULL;
			fopen_s(&pFile, filename, "rb");
			if (!pFile)
				return false;

			//비트맵파일헤더, 비트맵인포헤더 두 개가 존재하여 용량이 추가가 됨(bmp형태의 화소점을 읽어서 그림을 그려줄 수 있음)
			//이 두 가지가 제대로 정의가 안될 경우 파일은 만들어지지만 그림 파일을 읽을 수 없다
			BITMAPFILEHEADER fileHeader;

			if (!fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, pFile))
			{
				fclose(pFile);
				return false;
			}

			if (fileHeader.bfType != 0x4D42) // 'BM' 문자
			{
				fclose(pFile);
				return false;
			}
			BITMAPINFOHEADER infoHeader;

			if (!fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, pFile))
			{
				fclose(pFile);
				return false;
			}
			if (infoHeader.biBitCount != 8 && infoHeader.biBitCount != 24)
			{
				fclose(pFile);
				return false;
			}

			if (m_nWidth != infoHeader.biWidth && m_nHeight != infoHeader.biHeight && m_nChannels != infoHeader.biBitCount / 8)
			{
				if (m_pImageData)
					delete[] m_pImageData;

				m_nChannels = infoHeader.biBitCount / 8;
				m_nHeight = infoHeader.biHeight;
				m_nWidth = infoHeader.biWidth;
				m_nWStep = (m_nWidth * m_nChannels * sizrof(T) + 3) & ~3;

				m_pImageData = new T[m_nHeight * m_nWStep];
			}

			fseek(pFile, fileHeader.bfOffBits, SEEK_SET);

			int r;
			for (r = m_nHeight - 1; r >= 0; r--)
			{
				if (!fread(&m_pImageData[r * m_nWStep], sizrof(BYTE), m_nWStep, pFile))
				{
					fclose(pFile);
					return false;
				}
			}
			fclose(pFile);
			return true;
		}
		else
		{
			return false;
		}
	}
	bool SaveImage(const char* filename)
	{
		assert(sizeof(T) == 1);

		if (strcmp(".BMP", &filename[strlen(filename)] - 4))
		{
			FILE* pFile = NULL;
			fopen_s(&pFile, filename, "wb");
			if (!pFile)
				return false;

			BITMAPFILEHEADER fileHeader;
			fileHeader.bfType = 0x4D42;
			fileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + m_nWStep * m_nHeight + (m_nChannels == 1) * 1024;
			fileHeader.bfReserved1 = 0;
			fileHeader.bfReserved2 = 0;
			fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (m_nChannels == 1) * 256 * sizeof(RGBQUAD);

			fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, pFile);

			BITMAPINFOHEADER infoHeader;
			infoHeader.biSize = sizeof(BITMAPINFOHEADER);
			infoHeader.biWidth = m_nWidth;
			infoHeader.biHeight = m_nHeight;
			infoHeader.biPlanes = 1;
			infoHeader.biBitCount = m_nChannels * 8;
			infoHeader.biCompression = BI_RGB;
			infoHeader.biSizeImage = m_nWStep * m_nHeight;
			infoHeader.biClrImportant = 0;
			infoHeader.biClrUsed = 0;
			infoHeader.biXPelsPerMeter = 0;
			infoHeader.biYPelsPerMeter = 0;

			fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);

			if (m_nChannels == 1)
			{
				for (int l = 0; l < 256; l++)
				{
					RGBQUAD GrayPalette = { l, l, l, 0 };
					fwrite(&GrayPalette, sizeof(RGBQUAD), 1, pFile);
				}
			}

			int r;
			for (r = m_nHeight - 1; r >= 0; r--)
			{
				fwrite(&m_pImageData[r * m_nWStep], sizeof(BYTE), m_nWStep, pFile);
			}
			fclose(pFile);
			return true;
		}
		else
		{
			return false;
		}
	}
	bool IsEmpty() const
	{
		return m_pImageData ? false : true;
	}
	void SetConstValue(T val)
	{
		if (val == 0)
		{
			memset(m_pImageData, 0, m_nWStep * m_nHeight * sizeof(T));
			return;
		}
		if (sizeof(T) == 1)
		{
			memset(m_pImageData, val, m_nWStep * m_nHeight);
		}
		else
		{
			T* pData = m_pImageData;
			for (int r = 0; r < m_nHeight; r++)
			{
				for (int c = 0; c < m_nWidth; c++)
				{
					pData[c] = val;
				}
				pData += m_nWStep;
			}
		}
	}
	inline T& GetAt(int x, int y, int c = 0) const //함수의 호출과 리턴을 하지 않고 사용하여 오버헤드 방지
	{
		assert(x >= 0 && x < m_nWidth&& y >= 0 && y < m_nHeight);
		return m_pImageData[m_nWStep * y + m_nChannels * x + c];
	}
	int GetChannel() const { return m_nChannels; }
	int GetHeight() const { return m_nHeight; }
	int GetWidth() const { return m_nWidth; }
	int GetWStep() const { return m_nWStep; }
	T* GetPtr(int r = 0, int c = 0) const { return m_pImageData + r * m_nWStep + c; }

protected:
	int m_nChannels;//채널 수 :  8비트 = 1바이트 = 1채널
	int m_nHeight; //세로 픽셀 수
	int m_nWidth; //가로 픽셀 수
	int m_nWStep; // 행당 데이터 원소 수 (4의 배수)
	T* m_pImageData; // 픽셀 배열 포인터
};

typedef CMyImage <BYTE> CByteImage;
typedef CMyImage <int> CIntImage;
typedef CMyImage <float> CFloatImage;
typedef CMyImage <double> CDoubleImage; //여러가지 자료형을 사용할 수 있게 여러가지 자료형을 구분해놓음

