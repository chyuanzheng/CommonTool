#pragma once

#include "stdAfx.h"
#include "iic.h"
class CM52795
{
		//52795��Ƶ����ʹ���ּ�
		//52795Ϊ��·����Ƶ���루��������������··����Ƶ���������������
		//��ַ��0x90���ӵͣ�0x92���Ӹߣ�
		//�ӵ�ַ��������Ƶ1����
		//���ݣ�������Ƶ2���أ�������Ʒ���ͬ��Ƶ1���أ������ӵ�ַд����ͬ.
		//�ӵ�ַ�����÷���
		//һ���ֽ�8��λ������Ϊ

		//ֵXXXXXXXX
		//λ76543210

		//����7��6���ڿ�����Ƶģʽ
		//7��6Ϊ00ʱ��ʾ����
		//7��6Ϊ01ʱ��ʾ���������
		//7��6Ϊ10ʱ��ʾ���������
		//7��6Ϊ11ʱΪ�����������

		//����5��4ΪIO�������
		//5Ϊ0ʱΪ�ߡ�1ʱΪ��
		//4Ϊ0ʱΪ�ߡ�1ʱΪ��

		//����3Ϊ�Ŵ���ǿ����
		//3Ϊ0ʱ���Ŵ�
		//3Ϊ1ʱ�Ŵ�6dB

		//����2����

		//����1��0���ڿ��������Ƶ
		//1��0Ϊ00ʱ��һ·��Ƶ���
		//1��0Ϊ01ʱ�ڶ�·��Ƶ���
		//1��0Ϊ10ʱ����·��Ƶ���
		//1��0Ϊ11ʱ����·��Ƶ���

		//���ӣ�
		//������Ҫ�����һ·���Ŵ���������ͬʱ���ʱ2���Ʊ�ʾ��
		//11110000
		//����·�Ŵ����������Ϊ��
		//10001010
		//����·���Ŵ������Ϊ��
		//00110011 
		BYTE WriteBytes[3];
		/// <summary>
		/// ��ʮ����Ϊ���õ�ַ�ţ�����ӵ����ַΪ0x90,����Ӹߵ�ַΪ0x92.

public:
		/// </summary>
		enum  LEVEL { Low, High };
		/// <summary>
		/// ����ѡ��
		/// </summary>
		enum  InputSele { TUNER, VIDEO2, VIDEO3, VIDEO4 };
		/// <summary>
		/// ���ѡ��
		/// </summary>
		enum  OutputSele { V1OUT, V2OUT, ALL }; 
		/// <summary>
		/// �Ŵ�
		/// </summary>

		/// <summary>
		/// ����ģʽ
		/// </summary>
		enum  AudioMode { MUTE, RIGHT, LEFT, NORMAL };
		/// <summary>
		/// ���I/O���ƿ�
		/// </summary>
		enum  IOoutPort{ DC, DD, D4, D5 };
		InputSele curInput1;
		InputSele curInput2;
public:
		CM52795()
		{
			WriteBytes[0] = 0x92;             // Ĭ�ϵ�ַΪ0x48(��λ��ַ)
			WriteBytes[1] = 0xF8;                  // ���ڿ��Ƶ�һ����ڣ�Ĭ��Ϊ��һ������Ϊ���������Ϊ���Ŵ���������
			WriteBytes[2] = 0xF8;                  // ���ڿ��Ƶڶ�����ڣ�Ĭ��Ϊ��һ������Ϊ���������Ϊ���Ŵ���������
			curInput1 = TUNER;
			curInput2 = TUNER;
		}



		/// <summary>
		/// ���������ѡ��
		/// </summary>
		/// <param name="pOutputSele"></param>
		/// <param name="pInputSelect">�������Ƶ�ӿ�</param>
		/// <returns>�Ƿ�ɹ�ѡ��</returns>
		BOOL InputSelect(OutputSele pOutputSele,InputSele pInputSelect)
		{
#ifdef UIONLY
			return 1;
#else
			WriteBytes[1] = 0xF0;		// ���Ŵ�
			WriteBytes[2] = 0xF0;
			//WriteBytes[1] = 0xF8;		// �Ŵ�6DB
			//WriteBytes[2] = 0xF8;
			if (pOutputSele == V1OUT)
			{
				curInput1 = pInputSelect;
			}
			if (pOutputSele == V2OUT)
			{
				curInput2 = pInputSelect;
			}
			if (pOutputSele == ALL)
			{
				curInput1 = curInput2 = pInputSelect;
			}
			WriteBytes[1] |= curInput1;
			WriteBytes[2] |= curInput2;
			return WriteIIC();
#endif
		}

		BOOL AutoSelect()
		{
			WriteBytes[1] = 0xF0;		// ���Ŵ�
			WriteBytes[2] = 0xF0;
			//WriteBytes[1] = 0xF8;		// �Ŵ�6DB
			//WriteBytes[2] = 0xF8;
			curInput2 = curInput1;
			WriteBytes[1] |= curInput1;
			WriteBytes[2] |= curInput2;
			return WriteIIC();
		}

		/// <summary>
		/// �Ŵ�ѡ��
		/// </summary>
		/// <param name="pOutputSele">�������Ƶ�ӿ�</param>
		/// <param name="pGain">�Ƿ�Ŵ�</param>
		/// <returns>�Ƿ���Ƴɹ�</returns>
		BOOL AmpGain(OutputSele pOutputSele, LEVEL pGain)
		{
#ifdef UIONLY
			return 1;
#else
			byte ZeroBit = 251;// OxFB;        // &11111011,��������λ���㡣�����������Ҫ���Ƶ�λ
			byte CONTROL = 0x00;        // ���ڿ��ƵĲ���
			if (pGain == High)
			{
				CONTROL = 0x04; //��Ӧ����λΪ1
			}
			else
			{
				CONTROL = 0x00; //��Ӧ����λΪ0
			}
			Outputselect(pOutputSele, ZeroBit, CONTROL);
			return WriteIIC();
#endif
		}
		/// <summary>
		/// ����ģʽѡ��
		/// </summary>
		/// <param name="pOutputSele">�������Ƶ�ӿ�</param>
		/// <param name="pAudioMode">����ģʽ</param>
		/// <returns>�Ƿ�ɹ�ѡ��</returns>
		BOOL AudioModeSelect(OutputSele pOutputSele, AudioMode pAudioMode)
		{
#ifdef UIONLY
			return 1;
#else
			byte ZeroBit = 63;// Ox3f;        // &00111111,��ǰ��λ���㡣�����������Ҫ���Ƶ�λ
			byte CONTROL = 0x00;        // ���ڿ��ƵĲ���
			switch (pAudioMode)
			{
			case MUTE:
				{
					CONTROL = 0x00; //7��6Ϊ00ʱ��ʾ����
					break;
				}
			case RIGHT:
				{
					CONTROL = 0x40; //7��6Ϊ01ʱ��ʾ���������
					break;
				}
			case LEFT:
				{
					CONTROL = 0x80; //7��6Ϊ10ʱ��ʾ���������
					break;
				}
			case NORMAL:
				{
					CONTROL = 0xC0; //7��6Ϊ11ʱΪ�����������
					break;
				}
			}
			Outputselect(pOutputSele, ZeroBit, CONTROL);
			return WriteIIC();
#endif
		}

		/// <summary>
		/// IO�ڿ���
		/// </summary>
		/// <param name="pIOoutPort">IO��ѡ��</param>
		/// <param name="pIOHighLow">IO������</param>
		/// <returns>�Ƿ�ɹ�����</returns>
		BOOL IOoutControl(IOoutPort pIOoutPort,LEVEL pIOHighLow)
		{
#ifdef UIONLY
			return 1;
#else
			byte ZeroBit4 = 239;// OxEF;        // &11101111,�����λ���㡣�����������Ҫ���Ƶ�λ
			byte ZeroBit5 = 223;// OxDF;        // &11011111,�����λ���㡣�����������Ҫ���Ƶ�λ
			switch (pIOoutPort)
			{
			case DC:
				{
					if (pIOHighLow == High)
					{
						WriteBytes[2] &= ZeroBit4;
						WriteBytes[2] |= 0x00;
					}
					else    // pIOHighLow == IOHighLow.Low
					{
						WriteBytes[2] &= ZeroBit4;
						WriteBytes[2] |= 0x10;
					}
					break;
				}
			case DD:
				{
					if (pIOHighLow == High)
					{
						WriteBytes[2] &= ZeroBit5;
						WriteBytes[2] |= 0x00;
					}
					else    // pIOHighLow == IOHighLow.Low
					{
						WriteBytes[2] &= ZeroBit5;
						WriteBytes[2] |= 0x20;
					}

					break;
				}
			case D4:
				{
					if (pIOHighLow == High)
					{
						WriteBytes[1] &= ZeroBit4;
						WriteBytes[1] |= 0x00;
					}
					else    // pIOHighLow == IOHighLow.Low
					{
						WriteBytes[1] &= ZeroBit4;
						WriteBytes[1] |= 0x10;
					}

					break;
				}
			case D5:
				{
					if (pIOHighLow == High)
					{
						WriteBytes[1] &= ZeroBit5;
						WriteBytes[1] |= 0x00;
					}
					else    // pIOHighLow == IOHighLow.Low
					{
						WriteBytes[1] &= ZeroBit5;
						WriteBytes[1] |= 0x20;
					}

					break;
				}
			}
			return WriteIIC();
#endif
		}
		/// <summary>
		/// ���ѡ��
		/// </summary>
		/// <param name="pOutputSele">���ѡ��</param>
		/// <param name="ZeroBit">����λ</param>
		/// <param name="CONTROL">����λ</param>
	private:
		void Outputselect(OutputSele pOutputSele, byte ZeroBit, byte CONTROL)
		{
#ifdef UIONLY
			return;
#else
			WriteBytes[1] = 0xF0;		// ���Ŵ�
			WriteBytes[2] = 0xF0;
			//WriteBytes[1] = 0xF8;		// �Ŵ�6DB
			//WriteBytes[2] = 0xF8;
			switch (pOutputSele)
			{
			case V1OUT:
				{
					WriteBytes[1] &= ZeroBit;
					WriteBytes[1] |= CONTROL;
					break;
				}
			case V2OUT:
				{
					WriteBytes[2] &= ZeroBit;
					WriteBytes[2] |= CONTROL;
					break;
				}
			case ALL:
				{
					WriteBytes[1] &= ZeroBit;
					WriteBytes[1] |= CONTROL;
					WriteBytes[2] &= ZeroBit;
					WriteBytes[2] |= CONTROL;
					break;
				}
			default:
				{
					WriteBytes[1] &= ZeroBit;
					WriteBytes[1] |= CONTROL;
					WriteBytes[2] &= ZeroBit;
					WriteBytes[2] |= CONTROL;
					break;
				}
			}
#endif
		}
		/// <summary>
		/// I2Cд��
		/// </summary>
		BOOL WriteIIC()
		{
#ifdef UIONLY
			return 1;
#else
			return IICWrite4(WriteBytes,3);
#endif
		}


};